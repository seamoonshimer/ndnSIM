// EdgeComputer-Freshness.cpp

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/ndnSIM-module.h"

#include "ns3/command-line.h"
#include "ns3/double.h"
#include "ns3/names.h"
#include "ns3/point-to-point-channel.h"
#include "ns3/uinteger.h"
  
#include "ns3/ndnSIM/helper/ndn-app-helper.hpp"
#include "ns3/ndnSIM/helper/ndn-global-routing-helper.hpp"
#include "ns3/ndnSIM/helper/ndn-stack-helper.hpp"
#include "ns3/ndnSIM/helper/ndn-strategy-choice-helper.hpp"
#include "ns3/ndnSIM/model/ndn-l3-protocol.hpp"
#include "ns3/ndnSIM/model/ndn-net-device-transport.hpp"
#include "ns3/ndnSIM/NFD/daemon/fw/best-route-strategy2.hpp"
#include "ns3/ndnSIM/utils/topology/annotated-topology-reader.hpp"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("EdgeComputer");

/*
void
displayRoutes(const NodeContainer& allNodes, const std::string& prefix)
{
    for (const auto& n : allNodes) {
    const auto& fib = n->GetObject<ndn::L3Protocol>()->getForwarder()->getFib();
    const auto& e = fib.findLongestPrefixMatch(prefix);
 
    std::cout << "Node " << n->GetId() << ", prefix: " << prefix << "\n";
 
    for (const auto& nh : e.getNextHops()) {
      std::cout << "4" << endl;
      // Get remote nodeId from face:
      const auto transport = dynamic_cast<ndn::NetDeviceTransport*>(nh.getFace().getTransport());
      if (transport == nullptr)
      { std::cout << "1" << endl;
        continue;}
 
      const auto nd1 = transport->GetNetDevice()->GetObject<PointToPointNetDevice>();
      if (nd1 == nullptr)
      { std::cout << "2" << endl;
        continue;}
 
      const auto ppChannel = DynamicCast<PointToPointChannel>(nd1->GetChannel());
      if (ppChannel == nullptr)
      { std::cout << "3" << endl;
        continue;}
 
      auto nd2 = ppChannel->GetDevice(0);
      if (nd2->GetNode() == n)
        nd2 = ppChannel->GetDevice(1);
 
      std::cout << "    NextHop: " << nd2->GetNode()->GetId() << ", cost: " << nh.getCost() << "\n";
    }
    std::cout << "\n";
  }
}
*/

/* 
void AddEntryCallback(std::string context, Ptr< const Entry > entry){
    std::cout << "asdfh"<<endl;   
}
*/

static void
changezipf(const std::string& prefix, int& n, int& time, std::string& Updataing)
{
  int num = n + 20;
  std::string numstr = std::to_string(num);
  
  num = time / 10;
  std::string updata = std::to_string(num);
  updata = prefix + updata;

  Config::Set("/NodeList/" + numstr + "/ApplicationList/*/$ns3::ndn::ConsumerZipfMandelbrot/Prefix", StringValue(updata));
//  std::cout << time << "s update:" << updata << " in node" << numstr << endl;                                                                                  //LOG
}

//static void
/*display()
{
  std::cout << "hello,hello!" << std::endl;
  Simulator::Schedule(Seconds(1.0),&display);
}
*/
    
/*display(Ptr<Node> node)
{
  Ptr<ndn::ContentStore> cs = node->GetObject<ndn::ContentStore>();
  Ptr<ndn::cs::Entry> current = cs->Begin();
  std::string string;
//  string = string + current->GetName().toUri();
  current->GetContentStore();
  std::cout << node->GetId() <<std::endl;
}
*/

int
main(int argc, char* argv[])
{
//  LogComponentEnable ("ndn.ConsumerZipfMandelbrot",LOG_LEVEL_INFO);                                                       //LOG
//  LogComponentEnable ("ndn.Producer",LOG_LEVEL_INFO);                                                                     //LOG
//变量  
  std::string CachePolicy = "0000";
  std::string RoutePolicy = "best-route"; 
  std::string FIBPolicy = "All";
  std::string Updataing = "No";

//  std::string TraceFile = "0000-0-0";
  
  std::string CacheNameOrder = "0000";
  std::string RouteNameOrder = "0";
  std::string FIBNameOrder = "0";
  std::string UpdataNameOrder = "0";

  CommandLine cmd;
  cmd.AddValue("CachePolicy","Set cache policy? (Default:Lru)",CachePolicy);
  cmd.AddValue("RoutePolicy","Set route polocy? (Default:best-route)",RoutePolicy);
  cmd.AddValue("FIBPolicy","Set FIB fulling polocy? (Default:All)",FIBPolicy);
  cmd.AddValue("Updataing","Set content updata? (Default:No)",Updataing);
//  cmd.AddValue("TraceFile","Set name of TraceFile? (Default:0000-0-0)",TraceFile);
  cmd.Parse(argc,argv);

  AnnotatedTopologyReader topologyReader("", 1);
  topologyReader.SetFileName("ndnsim/topologies/EdgeComputer-2.0.txt");
  topologyReader.Read();

  NodeContainer L0;
  L0.Add(Names::Find<Node>("c1"));
  
  NodeContainer L1;
  L1.Add(Names::Find<Node>("g1"));
  
  NodeContainer L2;
  L2.Add(Names::Find<Node>("s1"));
  L2.Add(Names::Find<Node>("s2"));
  
  NodeContainer L3;
  L3.Add(Names::Find<Node>("s3"));
  L3.Add(Names::Find<Node>("s4"));
  L3.Add(Names::Find<Node>("s5"));
  L3.Add(Names::Find<Node>("s6"));
  
  NodeContainer L4;
  L4.Add(Names::Find<Node>("r1"));
  L4.Add(Names::Find<Node>("r2"));
  L4.Add(Names::Find<Node>("r3"));
  L4.Add(Names::Find<Node>("r4"));
  L4.Add(Names::Find<Node>("r5"));
  L4.Add(Names::Find<Node>("r6"));
  L4.Add(Names::Find<Node>("r7"));
  L4.Add(Names::Find<Node>("r8"));
  L4.Add(Names::Find<Node>("r9"));
  L4.Add(Names::Find<Node>("r10"));
  L4.Add(Names::Find<Node>("r11"));
  L4.Add(Names::Find<Node>("r12"));
/*
  NodeContainer LD4;
  LD4.Add(Names::Find<Node>("d1"));
  LD4.Add(Names::Find<Node>("d2"));
  LD4.Add(Names::Find<Node>("d3"));
  LD4.Add(Names::Find<Node>("d4"));
  LD4.Add(Names::Find<Node>("d5"));
  LD4.Add(Names::Find<Node>("d6"));
  LD4.Add(Names::Find<Node>("d7"));
  LD4.Add(Names::Find<Node>("d8"));
 
  NodeContainer LR4;              
  LR4.Add(Names::Find<Node>("r1"));
  LR4.Add(Names::Find<Node>("r2"));
  LR4.Add(Names::Find<Node>("r3"));
  LR4.Add(Names::Find<Node>("r4")); 
*/
  NodeContainer L5;
  L5.Add(Names::Find<Node>("u1"));
  L5.Add(Names::Find<Node>("u2"));
  L5.Add(Names::Find<Node>("u3"));
  L5.Add(Names::Find<Node>("u4"));
  L5.Add(Names::Find<Node>("u5"));
  L5.Add(Names::Find<Node>("u6"));
  L5.Add(Names::Find<Node>("u7"));
  L5.Add(Names::Find<Node>("u8"));
  L5.Add(Names::Find<Node>("u9"));
  L5.Add(Names::Find<Node>("u10"));
  L5.Add(Names::Find<Node>("u11"));
  L5.Add(Names::Find<Node>("u12"));

  // 安装 NDN 协议栈
  ndn::StackHelper ndnHelper;
  ndnHelper.SetOldContentStore("ns3::ndn::cs::Nocache");
  ndnHelper.Install(L0);
  ndnHelper.Install(L5);
  //ndnHelper.Install(LD4);

    // 简单替换
for (int i = 0; i < 4; i++){

  if (CachePolicy[i] == '0'){
     ndnHelper.SetOldContentStore("ns3::ndn::cs::Nocache");
     CacheNameOrder[i] = '0';
  }
  else if (CachePolicy[i] == '1'){
     ndnHelper.SetOldContentStore("ns3::ndn::cs::Lru");
    // ndnHelper.SetOldContentStore("ns3::ndn::cs::Freshness::Lru");
     CacheNameOrder[i] = '1';
  }
  else if (CachePolicy[i] == '2'){
     ndnHelper.SetOldContentStore("ns3::ndn::cs::Fifo");
     CacheNameOrder[i] = '2';
  }
  else if (CachePolicy[i] == '3'){
     ndnHelper.SetOldContentStore("ns3::ndn::cs::Lfu");
     CacheNameOrder[i] = '3';
  }
  else if (CachePolicy[i] == '4'){
     ndnHelper.SetOldContentStore("ns3::ndn::cs::Random");
    // ndnHelper.SetOldContentStore("ns3::ndn::cs::Stats::Random");
     CacheNameOrder[i] = '4';
  }
    else{
     NS_LOG_UNCOND ("Error in CachePolicy !");   
  }


  if (i == 0)
     ndnHelper.Install(L1);
  else if (i == 1)
    ndnHelper.Install(L2);
  else if (i == 2)
    ndnHelper.Install(L3);
  else if (i == 3)
    ndnHelper.Install(L4);


    // 生存时间
//  ndnHelper.SetOldContentStore("ns3::ndn::cs::Stats::Lru");
//  ndnHelper.SetOldContentStore("ns3::ndn::cs::Stats::Fifo");
//  ndnHelper.SetOldContentStore("ns3::ndn::cs::Stats::Lfu");
//  ndnHelper.SetOldContentStore("ns3::ndn::cs::Stats::Random");
    
    // 新鲜度
//  ndnHelper.SetOldContentStore("ns3::ndn::cs::Freshness::Lru");
//  ndnHelper.SetOldContentStore("ns3::ndn::cs::Freshness::Fifo");
//  ndnHelper.SetOldContentStore("ns3::ndn::cs::Freshness::Lfu");
//  ndnHelper.SetOldContentStore("ns3::ndn::cs::Freshness::Random");
    
    // 概率性
//  ndnHelper.SetOldContentStore("ns3::ndn::cs::Probability::Lru");
//  ndnHelper.SetOldContentStore("ns3::ndn::cs::Probability::Fifo");
//  ndnHelper.SetOldContentStore("ns3::ndn::cs::Probability::Lfu");
//  ndnHelper.SetOldContentStore("ns3::ndn::cs::Probability::Random");

//  ndnHelper.InstallAll();

}
    
  // 设置 CS 内容存储库的容量，
    // 云中心
//  Config::Set("/NodeList/0/$ns3::ndn::ContentStore/MaxSize", UintegerValue(1000));
  
    // 网关
if (CacheNameOrder[0] != '0'){
  Config::Set("/NodeList/1/$ns3::ndn::ContentStore/MaxSize", UintegerValue(200));
}  
    // 出口交换器 
if (CacheNameOrder[1] != '0'){
  Config::Set("/NodeList/2/$ns3::ndn::ContentStore/MaxSize", UintegerValue(150));
  Config::Set("/NodeList/3/$ns3::ndn::ContentStore/MaxSize", UintegerValue(150));
}
    // 核心交换器
if (CacheNameOrder[2] != '0'){
  Config::Set("/NodeList/4/$ns3::ndn::ContentStore/MaxSize", UintegerValue(100));
  Config::Set("/NodeList/5/$ns3::ndn::ContentStore/MaxSize", UintegerValue(100));
  Config::Set("/NodeList/6/$ns3::ndn::ContentStore/MaxSize", UintegerValue(100));
  Config::Set("/NodeList/7/$ns3::ndn::ContentStore/MaxSize", UintegerValue(100));
}  
    // 路由器 + 边缘设备
if (CacheNameOrder[3] != '0'){
  Config::Set("/NodeList/8/$ns3::ndn::ContentStore/MaxSize", UintegerValue(50));
  Config::Set("/NodeList/9/$ns3::ndn::ContentStore/MaxSize", UintegerValue(50));
  Config::Set("/NodeList/10/$ns3::ndn::ContentStore/MaxSize", UintegerValue(50));
  Config::Set("/NodeList/11/$ns3::ndn::ContentStore/MaxSize", UintegerValue(50));
  Config::Set("/NodeList/12/$ns3::ndn::ContentStore/MaxSize", UintegerValue(50));
  Config::Set("/NodeList/13/$ns3::ndn::ContentStore/MaxSize", UintegerValue(50));
  Config::Set("/NodeList/14/$ns3::ndn::ContentStore/MaxSize", UintegerValue(50));
  Config::Set("/NodeList/15/$ns3::ndn::ContentStore/MaxSize", UintegerValue(50));
  Config::Set("/NodeList/16/$ns3::ndn::ContentStore/MaxSize", UintegerValue(50));
  Config::Set("/NodeList/17/$ns3::ndn::ContentStore/MaxSize", UintegerValue(50));
  Config::Set("/NodeList/18/$ns3::ndn::ContentStore/MaxSize", UintegerValue(50));
  Config::Set("/NodeList/19/$ns3::ndn::ContentStore/MaxSize", UintegerValue(50));
}
    // 用户
/*  Config::Set("/NodeList/20/$ns3::ndn::ContentStore/MaxSize", UintegerValue(1));
  Config::Set("/NodeList/21/$ns3::ndn::ContentStore/MaxSize", UintegerValue(1));
  Config::Set("/NodeList/22/$ns3::ndn::ContentStore/MaxSize", UintegerValue(1));
  Config::Set("/NodeList/23/$ns3::ndn::ContentStore/MaxSize", UintegerValue(1));
  Config::Set("/NodeList/24/$ns3::ndn::ContentStore/MaxSize", UintegerValue(1));
  Config::Set("/NodeList/25/$ns3::ndn::ContentStore/MaxSize", UintegerValue(1));
  Config::Set("/NodeList/26/$ns3::ndn::ContentStore/MaxSize", UintegerValue(1));
  Config::Set("/NodeList/27/$ns3::ndn::ContentStore/MaxSize", UintegerValue(1));
  Config::Set("/NodeList/28/$ns3::ndn::ContentStore/MaxSize", UintegerValue(1));
  Config::Set("/NodeList/29/$ns3::ndn::ContentStore/MaxSize", UintegerValue(1));
  Config::Set("/NodeList/30/$ns3::ndn::ContentStore/MaxSize", UintegerValue(1));
  Config::Set("/NodeList/31/$ns3::ndn::ContentStore/MaxSize", UintegerValue(1));
*/

  // 设置路由策略
  if (RoutePolicy == "best-route"){
    ndn::StrategyChoiceHelper::InstallAll("/", "/localhost/nfd/strategy/best-route");
    RouteNameOrder = "1";
  }
  else if (RoutePolicy == "multicast"){
    ndn::StrategyChoiceHelper::InstallAll("/", "/localhost/nfd/strategy/multicast");
    RouteNameOrder = "2";
  }
  else if (RoutePolicy == "ncc"){
    ndn::StrategyChoiceHelper::InstallAll("/", "/localhost/nfd/strategy/ncc");
    RouteNameOrder = "3";
  }
  else if (RoutePolicy == "client-control"){
    ndn::StrategyChoiceHelper::InstallAll("/", "/localhost/nfd/strategy/client-control");
    RouteNameOrder = "4";
  }
  else{
      NS_LOG_UNCOND ("Error in RoutePolicy");
  }
  topologyReader.ApplyOspfMetric();

  // 在所有节点上安装路由接口
  ndn::GlobalRoutingHelper ndnGlobalRoutingHelper;
  ndnGlobalRoutingHelper.InstallAll();

  // 获得消费者/生产者容器
  Ptr<Node> producer = Names::Find<Node>("c1");
  NodeContainer consumerNodes;
  consumerNodes.Add(Names::Find<Node>("u1"));
  consumerNodes.Add(Names::Find<Node>("u2"));
  consumerNodes.Add(Names::Find<Node>("u3"));
  consumerNodes.Add(Names::Find<Node>("u4"));
  consumerNodes.Add(Names::Find<Node>("u5"));
  consumerNodes.Add(Names::Find<Node>("u6"));
  consumerNodes.Add(Names::Find<Node>("u7"));
  consumerNodes.Add(Names::Find<Node>("u8"));
  consumerNodes.Add(Names::Find<Node>("u9"));
  consumerNodes.Add(Names::Find<Node>("u10"));
  consumerNodes.Add(Names::Find<Node>("u11"));
  consumerNodes.Add(Names::Find<Node>("u12"));

  // 安装 NDN 应用 - 消费者
//  ndn::AppHelper consumerHelper("ns3::ndn::ConsumerCbr");
//  ndn::AppHelper consumerHelper("ns3::ndn::ConsumerBatches");
//  ndn::AppHelper consumerHelper("ns3::ndn::ConsumerWindow");
//  ndn::AppHelper consumerHelper("ns3::ndn::ConsumerPcon");

  std::string prefix1 = "/news";                                       // 前缀1-news
  std::string prefix2 = "/game";                                       // 前缀2-game
  std::string prefix3 = "/sport";                                      // 前缀3-sport
  std::string prefix4 = "/music";                                      // 前缀4-music
  std::string prefix5 = "/movie";                                      // 前缀5-movie
  ndn::AppHelper consumerHelper("ns3::ndn::ConsumerZipfMandelbrot");    // Zipf 分布的兴趣包请求，默认100种类型的内容请求
  
  consumerHelper.SetPrefix("/");                                    // 设置兴趣包前缀
  consumerHelper.SetAttribute("Frequency", StringValue("50"));           // 设置兴趣包请求频率
  consumerHelper.SetAttribute("q", StringValue("0.7"));           // 设置q
  consumerHelper.SetAttribute("s", StringValue("0.7"));           // 设置s
  consumerHelper.SetAttribute("NumberOfContents", StringValue("200"));    // 设置兴趣包种类
  
/*  if(RoutePolicy == "multicast")
    consumerHelper.SetAttribute("NumberOfContents", StringValue("50"));    // 设置兴趣包种类
  else
    consumerHelper.SetAttribute("NumberOfContents", StringValue("100"));    // 设置兴趣包种类
*/
  //consumerHelper.SetAttribute ("Randomize", StringValue ("uniform")); // 设置随机属性

  consumerHelper.Install(consumerNodes);

  for(int i = 0; i < 20; i++){                                           //改变次数
    int TIME[20][20] = {
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    26,3,5,2,5,10,5,14,6,2,6,5,4,13,12,4,8,6,17,2,
    34,4,18,16,14,13,8,17,14,3,12,11,7,16,14,11,10,10,23,5,
    35,10,30,18,17,25,15,20,21,4,14,15,20,24,23,14,11,19,24,8,
    42,15,33,22,19,30,17,24,30,10,16,18,38,25,25,25,13,21,27,12,
    43,16,34,29,22,39,26,30,33,19,18,20,41,33,32,26,16,26,29,25,
    44,18,37,34,24,40,35,32,43,24,20,26,46,35,36,28,21,29,33,35,
    49,22,45,36,26,43,39,34,48,28,21,28,50,38,37,30,23,43,37,41,
    56,43,50,37,31,55,43,40,50,40,30,39,53,40,53,31,25,48,43,44,
    61,44,58,42,41,56,45,41,51,47,40,47,57,46,66,42,35,49,47,45,
    63,45,62,48,44,57,55,43,53,48,50,49,61,51,67,43,48,50,56,52,
    64,47,68,57,45,66,56,47,55,57,59,50,63,54,70,64,52,52,64,67,
    67,61,69,60,57,72,60,56,56,58,66,57,64,55,71,65,63,58,70,75,
    71,76,81,65,60,74,65,66,62,61,71,61,68,58,73,68,64,66,74,76,
    78,77,86,67,67,76,66,72,66,71,79,65,69,63,78,73,66,67,79,80,
    80,83,92,76,71,78,71,81,69,79,87,74,76,64,79,77,79,70,84,83,
    84,94,93,96,77,88,73,86,70,90,91,76,79,69,84,79,85,72,85,89,
    88,95,96,97,78,90,79,92,72,94,94,77,86,74,89,80,88,91,86,90,
    91,98,97,98,87,93,89,93,90,95,97,82,87,86,94,85,96,92,87,92,
    92,99,99,99,95,98,96,97,91,99,99,85,91,99,98,90,97,99,99,97};
    
    std::string CONTENT[20][20] = {                                     //遍历20个节点
    "4","5","5","2","1","2","4","2","4","4","3","3","1","2","3","5","3","3","4","3",
    "5","2","3","2","4","2","3","3","4","1","5","5","4","5","3","3","4","3","4","2",
    "4","2","1","1","4","2","1","3","1","1","2","4","2","4","5","5","2","4","2","1",
    "1","3","1","2","1","2","3","2","5","5","4","4","4","1","4","4","1","2","2","2",
    "4","1","1","3","2","3","4","3","3","4","4","5","3","4","1","5","5","3","3","3",
    "3","4","2","3","4","5","2","1","3","1","3","2","3","5","4","1","4","3","4","1",
    "4","5","4","3","4","4","4","5","5","4","4","2","4","2","2","4","4","3","3","5",
    "4","3","2","5","2","5","4","4","5","1","2","5","2","4","2","3","3","5","2","5",
    "2","4","3","2","5","2","2","4","4","4","3","4","3","2","2","4","3","3","1","4",
    "2","3","4","2","2","2","4","4","2","1","3","4","5","4","4","3","2","3","2","2",
    "2","5","3","3","5","2","4","3","2","3","3","5","4","5","3","4","2","3","3","4",
    "5","2","3","4","4","2","2","3","1","3","4","4","3","2","4","4","3","3","4","2",
    "2","3","2","4","4","4","4","4","1","2","3","4","3","4","3","3","3","5","4","4",
    "2","3","4","2","2","5","2","3","2","2","2","1","4","3","3","2","4","2","1","2",
    "3","4","3","4","3","2","4","4","2","3","2","3","5","4","4","2","1","2","3","5",
    "1","3","3","5","3","3","2","2","2","3","1","4","3","1","4","5","4","1","3","5",
    "4","2","3","3","2","2","4","2","3","2","4","3","1","4","3","3","3","2","5","1",
    "1","5","5","3","2","4","1","4","3","4","5","2","2","3","5","4","1","5","2","4",
    "3","3","4","3","1","4","4","4","4","4","3","4","5","1","5","3","3","2","4","3",
    "3","4","2","3","3","2","4","4","5","2","1","1","4","3","1","2","3","1","2","4"};
   
    for(int j = 0; j < 12; j++){
      std::string prefix;

      if(CONTENT[i][j] == "1")
        prefix = prefix1;
      else if(CONTENT[i][j] == "2")
        prefix = prefix2;
      else if(CONTENT[i][j] == "3")
        prefix = prefix3;
      else if(CONTENT[i][j] == "4")
        prefix = prefix4;
      else
        prefix = prefix5;
      
      Simulator::Schedule(Seconds(TIME[i][j]), &changezipf, prefix, j, TIME[i][j], Updataing);
    }
    i = i + 1;
  }

  // 安装 NDN 应用 - 生产者
  ndn::AppHelper producerHelper("ns3::ndn::Producer");
  producerHelper.SetAttribute("PayloadSize", StringValue("1024"));
  producerHelper.SetAttribute("Freshness", TimeValue(Seconds(10.0)));
  
  producerHelper.SetPrefix("/");
  producerHelper.Install(producer);

  // 添加生成源前缀到全局路由
  ndnGlobalRoutingHelper.AddOrigins("/", producer);
  
  if(RoutePolicy == "multicast"){
  std::cout << "multicast" << std::endl;
//  ndnGlobalRoutingHelper.AddOrigins("/", L5);
  ndnGlobalRoutingHelper.AddOrigins("/", L4);}

  // 计算全局路由，填充 FIB 表
  if (FIBPolicy == "best-route"){
     ndn::GlobalRoutingHelper::CalculateRoutes();
     FIBNameOrder = "1";
  }
  else if (FIBPolicy == "Lfid"){
     ndn::GlobalRoutingHelper::CalculateLfidRoutes();
     FIBNameOrder = "2";
  }
  else if (FIBPolicy == "All"){
     ndn::GlobalRoutingHelper::CalculateAllPossibleRoutes();
     FIBNameOrder = "3";
  }
  else{
     NS_LOG_UNCOND ("Error in FIB Polocy !"); 
  }

//displayRoutes(topologyReader.GetNodes(), prefix);

  if(Updataing == "Yes")
    UpdataNameOrder = "1";

  // Trace 文件
  std::string TraceFile = CacheNameOrder + '-' + RouteNameOrder + '-' + FIBNameOrder + '-' + UpdataNameOrder;
  ndn::AppDelayTracer::InstallAll(TraceFile + "-Packet-delays-trace.txt");
  ndn::CsTracer::InstallAll(TraceFile + "-Cache-hit-trace.txt");
  ndn::L3RateTracer::InstallAll(TraceFile + "-Traffic-trace.txt");
  L2RateTracer::InstallAll(TraceFile + "-Drop-trace.txt");

//  Simulator::Schedule(Seconds(2.0), &display, L1.Get(0));
//  Simulator::Schedule(Seconds(1.0), &display);
/*
  Config::Connect("DidAddEntry",MakeCallback(&AddEntryCallback));
*/
  // 设置实验时长
  Simulator::Stop(Seconds(100.0));
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
