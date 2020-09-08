// Idea-ib.cc

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/ndnSIM-module.h"

namespace ns3 {

static void
ReSetPrefix(int& updata, int& Imbalance){
 for(int i = 0; i < 16; i++){
   int node = 32 + i;
   for(int j = 0; j < 16 - Imbalance; j++){
     std::string prefix = "/prefix";
     char c = 'a' + (i + j) % 16;                       
     prefix += c;
     std::string str = prefix + std::to_string(updata);
     Config::Set("/NodeList/" + std::to_string(node) + "/ApplicationList/" + std::to_string(j) + "/$ns3::ndn::ConsumerZipfMandelbrot/Prefix", StringValue(str));
   }
 }
}

int
main(int argc, char* argv[])
{
  LogComponentEnable("ndn.ConsumerZipfMandelbrot",LOG_LEVEL_INFO);
  LogComponentEnable("ndn.Producer",LOG_LEVEL_INFO);

  // 命令行参数
  std::string Policy = "Idea-ib";
  std::string Alpha = "1.0";
  //std::string Frequency = "5";
  int Frequency = 200;
  std::string NumberOfContents = "6250";
  std::string CSsize = "50";
  int Runtime = 201;
  int Updata = 5;
  //int Category = 16;
  int Imbalance = 15;

  CommandLine cmd;
  cmd.AddValue("Alpha","Alpha(1.0)",Alpha);
  cmd.AddValue("Frequency","Frequency(200)",Frequency);
  cmd.AddValue("NumberOfContents","NumberOfContents(6250)",NumberOfContents);
  cmd.AddValue("CSsize","CSsize(50)",CSsize);
  cmd.AddValue("Policy","Policy(Idea-ib)",Policy);
  cmd.AddValue("Runtime","Runtime(201)",Runtime);
  cmd.AddValue("Updata","Updata(5)",Updata);
  cmd.AddValue("Imbalance","Imbalance(15)",Imbalance);
  cmd.Parse(argc, argv);

  AnnotatedTopologyReader topologyReader("", 1);
  topologyReader.SetFileName("ndnsim/topologies/tree-topology.txt");
  topologyReader.Read();

  // 分层
    // Cloud
    NodeContainer L0;
    L0.Add(Names::Find<Node>("Cloud"));
    // Gateway
    NodeContainer L1;
    L1.Add(Names::Find<Node>("G1"));
    // Core switch
    NodeContainer L2;
    L2.Add(Names::Find<Node>("C1"));
    L2.Add(Names::Find<Node>("C2"));
    // Middle Switch
    NodeContainer L3;
    for (int i=1; i<=4; i++){
        L3.Add(Names::Find<Node>("M"+std::to_string(i)));
    }
    // Edge switch
    NodeContainer L4;
    for (int i=1; i<=8; i++){
        L4.Add(Names::Find<Node>("E"+std::to_string(i)));
    }
    // Room switch
    NodeContainer L5;
    for (int i=1; i<=16; i++){
        L5.Add(Names::Find<Node>("R"+std::to_string(i)));
    }
    // User
    NodeContainer L6;
    for (int i=1; i<=16; i++){
        L6.Add(Names::Find<Node>("U"+std::to_string(i)));
    }
  
  // 安装 NDN 协议栈
  ndn::StackHelper ndnHelper;
    ndnHelper.SetOldContentStore("ns3::ndn::cs::Lru","MaxSize","0");          // 发布节点存储容量 无限
    ndnHelper.Install(L0);
    ndnHelper.SetOldContentStore("ns3::ndn::cs::Lru","MaxSize",CSsize);         // 边缘节点存储容量 50
    ndnHelper.Install(L1);
    ndnHelper.Install(L2);
    ndnHelper.Install(L3);
    ndnHelper.Install(L4);
    ndnHelper.Install(L5);
    ndnHelper.SetOldContentStore("ns3::ndn::cs::Nocache");                    // 发布节点存储容量 无
    ndnHelper.Install(L6);

  // 设置路由策略为 最佳路径
  ndn::StrategyChoiceHelper::InstallAll("/", "/localhost/nfd/strategy/best-route");

  // 在所有节点上安装路由接口
  ndn::GlobalRoutingHelper ndnGlobalRoutingHelper;
  ndnGlobalRoutingHelper.InstallAll();

  // 获得消费者/生产者容器
  Ptr<Node> producer = Names::Find<Node>("Cloud");
  //NodeContainer consumerNodes;
  //consumerNodes = L6;
  //Ptr<Node> consumerNodes = Names::Find<Node>("U1");
  //consumerNodes.Add(Names::Find<Node>("U1"));
  //consumerNodes.Add(Names::Find<Node>("U2"));

  // 安装 NDN 应用 - 消费者
  //std::string prefix = "/prefix";                                        // 前缀
  ndn::AppHelper consumerHelper("ns3::ndn::ConsumerZipfMandelbrot");     // 消费者应用名称
  //consumerHelper.SetPrefix(prefix);                                      // 设置兴趣包前缀
  //consumerHelper.SetAttribute("Frequency", StringValue(Frequency));          // 设置兴趣包请求频率
  consumerHelper.SetAttribute("Randomize", StringValue ("exponential")); // 设置随机属性
  //consumerHelper.SetAttribute("Randomize", StringValue ("uniform")); // 设置随机属性
  consumerHelper.SetAttribute("q", StringValue(Alpha));                  // 设置参数q
  consumerHelper.SetAttribute("s", StringValue(Alpha));                  // 设置参数s

  consumerHelper.SetAttribute("NumberOfContents", StringValue(NumberOfContents));  // 设置兴趣包数量初始变量 (还需要在 zipf.cpp 中修改初始常量 m_N_First)
                                                                         // 兴趣包更新常量 （需要在 zipf.cpp 中修改常量 m_Public）
  
  // 多个消费者应用的部署
  for(int i = 0; i < 16; i++){                // 16 nodes loop
    for(int j = 0; j < 16 - Imbalance; j++){  // apps loop
      std::string prefix = "/prefix";
      char c = 'a' + (i + j) % 16;
      prefix += c;
      consumerHelper.SetPrefix(prefix+"0");                                                         // 设置兴趣包前缀
      std::string Fre = std::to_string(Frequency/(16-Imbalance));                               // 频率
      consumerHelper.SetAttribute("Frequency", StringValue(Fre));                               // 设置兴趣包请求频率
      consumerHelper.Install(Names::Find<Node>('U' + std::to_string(i+1)));                       // 安装到指定节点
    }
  }

  // 更新请求前缀
  for(int i = 1; i < Runtime/Updata; i++){
    Simulator::Schedule(Seconds(i*Updata), &ReSetPrefix, i, Imbalance);
  }
  
  // 安装 NDN 应用 - 生产者
  ndn::AppHelper producerHelper("ns3::ndn::Producer");
  producerHelper.SetPrefix("/");
  producerHelper.SetAttribute("PayloadSize", StringValue("1024"));
  producerHelper.Install(producer);

  // 添加生成源前缀到全局路由
  ndnGlobalRoutingHelper.AddOrigins("/", producer);

  // 计算全局路由，填充 FIB 表
  ndn::GlobalRoutingHelper::CalculateRoutes();

  ndn::AppDelayTracer::InstallAll(Policy+"-delays.txt");
  ndn::CsTracer::InstallAll(Policy+"-cs.txt");
  ndn::L3RateTracer::InstallAll(Policy+"-traffic.txt");
  L2RateTracer::InstallAll(Policy+"-drop.txt");

  // 设置实验时长
  Simulator::Stop(Seconds(Runtime));
  Simulator::Run();
  Simulator::Destroy();

  return 0;
}

} // namespace ns3

int
main(int argc, char* argv[])
{
  return ns3::main(argc, argv);
}
