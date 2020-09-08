// Ran-lh.cc

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/ndnSIM-module.h"

namespace ns3 {

static void
ReSetPrefix(const std::string& str, int& Level){
 for(int j = 122; j <= 202; j++){
  Config::Set("/NodeList/" + std::to_string(j) + "/ApplicationList/*/$ns3::ndn::ConsumerZipfMandelbrot/Prefix", StringValue(str));
 }
}

int
main(int argc, char* argv[])
{
  LogComponentEnable("ndn.ConsumerZipfMandelbrot",LOG_LEVEL_INFO);
  LogComponentEnable("ndn.Producer",LOG_LEVEL_INFO);

  // 命令行参数
  std::string Policy = "Ran-lh";
  std::string Alpha = "1.0";
  std::string Frequency = "200";
  std::string NumberOfContents = "100000";
  std::string CSsize = "50";
  int Runtime = 101;
  int Updata = 5;
  int Level = 5;

  CommandLine cmd;
  cmd.AddValue("Alpha","Alpha(1.0)",Alpha);
  cmd.AddValue("Frequency","Frequency(200)",Frequency);
  cmd.AddValue("NumberOfContents","NumberOfContents(100000)",NumberOfContents);
  cmd.AddValue("CSsize","CSsize(50)",CSsize);
  cmd.AddValue("Policy","Policy(Ran-lh)",Policy);
  cmd.AddValue("Runtime","Runtime(201)",Runtime);
  cmd.AddValue("Updata","Updata(5)",Updata);
  cmd.AddValue("Level","Level(1)",Level);
  cmd.Parse(argc, argv);

  AnnotatedTopologyReader topologyReader("", 1);
  topologyReader.SetFileName("ndnsim/topologies/3-tree-5-topology.txt");
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
    L2.Add(Names::Find<Node>("C3"));
    // Middle Switch
    NodeContainer L3;
    for (int i=1; i<=9; i++){
        L3.Add(Names::Find<Node>("M"+std::to_string(i)));
    }
    // Edge switch
    NodeContainer L4;
    for (int i=1; i<=27; i++){
        L4.Add(Names::Find<Node>("E"+std::to_string(i)));
    }
    // Room switch
    NodeContainer L5;
    for (int i=1; i<=81; i++){
        L5.Add(Names::Find<Node>("R"+std::to_string(i)));
    }
    // User
    NodeContainer L6;
    for (int i=1; i<=81; i++){
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

  NodeContainer LL;
  if (Level == 1){
    for (int i=1; i<=41; i++){
      if(i%3==0 || ((i-1)/3+1)%3==0 || ((i-1)/9+1)==3) continue;
      LL.Add(Names::Find<Node>("U"+std::to_string(i)));
     }
  }else if (Level == 2){
    for (int i=1; i<=42; i++){
      if(((i-1)/3+1)%3==0 || ((i-1)/9+1)==3) continue;
      LL.Add(Names::Find<Node>("U"+std::to_string(i)));
    }
  }else if (Level == 3){
    for (int i=1; i<=45; i++){
      if(((i-1)/9+1)==3) continue;
      LL.Add(Names::Find<Node>("U"+std::to_string(i)));
    }
  }else if (Level == 4){
    for (int i=1; i<=54; i++){
    LL.Add(Names::Find<Node>("U"+std::to_string(i)));
    }
  }else if (Level == 5){
    for (int i=1; i<=81; i++){
    LL.Add(Names::Find<Node>("U"+std::to_string(i)));
    }
  }

  // 获得消费者/生产者容器
  Ptr<Node> producer = Names::Find<Node>("Cloud");
  NodeContainer consumerNodes;
  consumerNodes = LL;
  //Ptr<Node> consumerNodes = Names::Find<Node>("U1");
  //consumerNodes.Add(Names::Find<Node>("U1"));
  //consumerNodes.Add(Names::Find<Node>("U2"));

  // 安装 NDN 应用 - 消费者
  std::string prefix = "/prefix";                                        // 前缀
  ndn::AppHelper consumerHelper("ns3::ndn::ConsumerZipfMandelbrot");     // 消费者应用名称
  consumerHelper.SetPrefix(prefix);                                      // 设置兴趣包前缀
  consumerHelper.SetAttribute("Frequency", StringValue(Frequency));          // 设置兴趣包请求频率
  consumerHelper.SetAttribute("Randomize", StringValue ("exponential")); // 设置随机属性
  consumerHelper.SetAttribute("q", StringValue(Alpha));                  // 设置参数q
  consumerHelper.SetAttribute("s", StringValue(Alpha));                  // 设置参数s

  consumerHelper.SetAttribute("NumberOfContents", StringValue(NumberOfContents));  // 设置兴趣包数量初始变量 (还需要在 zipf.cpp 中修改初始常量 m_N_First)
                                                                         // 兴趣包更新常量 （需要在 zipf.cpp 中修改常量 m_Public）
  consumerHelper.Install(consumerNodes);

  // 更新请求前缀
  for(int i = 1; i < Runtime/Updata; i++){
    std::string str = prefix + std::to_string(i);
    Simulator::Schedule(Seconds(i*Updata), &ReSetPrefix, str, Level);
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
