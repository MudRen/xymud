//Cracked by Roath
inherit F_CLEAN_UP;

#include <ansi.h>
#include <quest.h>

// the quest format is the following mapping:
// daoxing :     type     name     id            object         amount
//--------------------------------------------------------------------
//  1000   : ({ "find",  "秘笈",   "mi ji" ,     "",             "1" }), 
//  5000   : ({ "give",  "灾民",   "zai min" ,   "白银(silver)", "5" }), 
// 12000   : ({ "kill",  "白骨精", "baigu jing", "",             "3" });
 
//找一本秘笈，救济灾民五两银子，三打白骨精．．．．．．

mapping quests_food = ([
       5 : ({ "find", "花生豆",       "huasheng",           "", "1" }),
      10 : ({ "find", "炸鸡腿",       "jitui",              "", "1" }),
      15 : ({ "find", "桂花酒袋",     "jiudai",             "", "1" }),
      20 : ({ "find", "红烧狗肉",     "gou rou",            "", "1" }),
      50 : ({ "find", "醋坛子",       "tanzi",              "", "1" }),
      60 : ({ "find", "粗磁酒瓶",     "jiuping",            "", "1" }),
      70 : ({ "find", "茶壶",         "cha hu",             "", "1" }),
      80 : ({ "find", "茶干",         "cha gan",            "", "1" }),
     100 : ({ "find", "素菜馅包子",   "sucai bao",          "", "1" }),
     110 : ({ "find", "猪肉馅包子",   "zhurou bao",         "", "1" }),
     120 : ({ "find", "海鲜味包子",   "haixian bao",        "", "1" }),
     150 : ({ "find", "云南白药",     "yunnan baiyao",      "", "1" }),
     200 : ({ "find", "水煮蛋",       "egg",                "", "1" }),
     210 : ({ "find", "羊肉饼",       "roubing",            "", "1" }),
     220 : ({ "find", "羊皮大酒囊",   "jiunang",            "", "1" }),
     250 : ({ "find", "猕猴桃干",     "mihou taogan",       "", "1" }),
     290 : ({ "find", "花雕酒袋",     "jiudai",             "", "1" }),
     300 : ({ "find", "包子",         "bao",                "", "1" }),
     310 : ({ "find", "青葫芦",       "hulu",               "", "1" }),
     320 : ({ "find", "胡萝卜",       "carrot",             "", "1" }),
     330 : ({ "find", "豆豆",         "beans",              "", "1" }),
     330 : ({ "find", "小白菜",       "xbc",                "", "1" }),
     400 : ({ "find", "牛皮酒袋",     "jiudai",             "", "1" }),
     500 : ({ "find", "雪梨",         "xue li",             "", "1" }),
     530 : ({ "find", "桂花雪莲羹",   "guihua geng",        "", "1" }),
     550 : ({ "find", "雪莲",         "xue lian",           "", "1" }),
     600 : ({ "find", "粽子",         "zongzi",             "", "1" }),
     700 : ({ "find", "烤鸡",         "chicken",            "", "1" }),
     710 : ({ "find", "葡萄干",       "putao gan",          "", "1" }),
     800 : ({ "find", "江米酒",       "mijiu",              "", "1" }),
     810 : ({ "find", "饭",           "fan",                "", "1" }),
     820 : ({ "find", "年糕",         "nian gao",           "", "1" }),
     830 : ({ "find", "油葫芦",       "you hulu",           "", "1" }),
     840 : ({ "find", "盐",           "yan",                "", "1" }),
    1010 : ({ "find", "五香茶干",     "cha gan",            "", "1" }),
    1020 : ({ "find", "瓜子",         "gua zi",             "", "1" }),
    1030 : ({ "find", "花生米",       "huasheng mi",        "", "1" }),
    1040 : ({ "find", "素煎饺",       "jian jiao",          "", "1" }),
    1050 : ({ "find", "鲜肉水饺",     "shui jiao",          "", "1" }),
    1060 : ({ "find", "面片",         "mian pian",          "", "1" }),
    1070 : ({ "find", "面汤",         "mian tang",          "", "1" }),
    1080 : ({ "find", "刀削面",       "mian tiao",          "", "1" }),
    1090 : ({ "find", "阳春面",       "mian tiao",          "", "1" }),
    1100 : ({ "find", "细面",         "mian tiao",          "", "1" }),
    1110 : ({ "find", "钢丝面",       "mian tiao",          "", "1" }),
    1120 : ({ "find", "鸡丝面",       "mian tiao",          "", "1" }),
    1130 : ({ "find", "牛肉丝面",     "mian tiao",          "", "1" }),
    1140 : ({ "find", "盖浇面",       "mian tiao",          "", "1" }),
    1150 : ({ "find", "卤味面",       "mian tiao",          "", "1" }),
    1160 : ({ "find", "排骨面",       "mian tiao",          "", "1" }),
    1170 : ({ "find", "豆丝面",       "mian tiao",          "", "1" }),
    1180 : ({ "find", "羊杂碎面",     "mian tiao",          "", "1" }),
    1190 : ({ "find", "海鲜面",       "mian tiao",          "", "1" }),
    1200 : ({ "find", "馄饨面",       "mian tiao",          "", "1" }),
    1210 : ({ "find", "车仔面",       "mian tiao",          "", "1" }),
    1220 : ({ "find", "肉煮面",       "mian tiao",          "", "1" }),
    1230 : ({ "find", "长寿面",       "mian tiao",          "", "1" }),
    1240 : ({ "find", "长寿面",       "mian tiao",          "", "1" }),
    1250 : ({ "find", "老家招牌面",   "mian tiao",          "", "1" }),
    1280 : ({ "find", "[33m老虎肉[m","laohu rou",         "", "1" }),
    1300 : ({ "find", "熏腊肠",       "xun lachang",        "", "1" }),
    1310 : ({ "find", "醉子鸡",       "zui ziji",           "", "1" }),
    1320 : ({ "find", "五花焖肉",     "wuhua menrou",       "", "1" }),
    1330 : ({ "find", "青丝熏鱼",     "qingsi xunyu",       "", "1" }),
    1340 : ({ "find", "糖醋排骨",     "tangcu paigu",       "", "1" }),
    1350 : ({ "find", "京酱肉丝",     "jingjiang rousi",    "", "1" }),
    1360 : ({ "find", "油炝大虾",     "youqiang daxia",     "", "1" }),
    1370 : ({ "find", "脆皮烤鸭",     "cuipi kaoya",        "", "1" }),
    1380 : ({ "find", "红烧素鹅",     "hongshao sue",       "", "1" }),
    1390 : ({ "find", "宫保鸡丁",     "gongbao jiding",     "", "1" }),
    1400 : ({ "find", "麻辣肚丝",     "mala dusi",          "", "1" }),
    1410 : ({ "find", "红油肺片",     "hongyou feipian",    "", "1" }),
    1420 : ({ "find", "嫩汆猪肝",     "nenqiang zhugan",    "", "1" }),
    1430 : ({ "find", "走油脆肠",     "zouyou cuichang",    "", "1" }),
    1440 : ({ "find", "爆炒腰花",     "baochao yaohua",     "", "1" }),
    1450 : ({ "find", "细扒头肉",     "xipa tourou",        "", "1" }),
    1460 : ({ "find", "麝香冬笋",     "shexiang dongsun",   "", "1" }),
    1470 : ({ "find", "翡翠豆腐",     "feicui doufu",       "", "1" }),
    1480 : ({ "find", "三鲜腐竹",     "sanxian fuzhu",      "", "1" }),
    1490 : ({ "find", "时鲜蔬菜",     "shuxian shucai",     "", "1" }),
    1500 : ({ "find", "皮蛋瘦肉粥",   "pidan shourouzhou",  "", "1" }),
    1510 : ({ "find", "火腿竹笙羹",   "huotui zhushenggeng","", "1" }),
    1530 : ({ "find", "[31m香獐肉[m","xiangzhang rou",     "", "1" }),
    1580 : ({ "find", "[33m狐狸肉[m","huli rou",           "", "1" }),
    1600 : ({ "find", "茶盏",         "cha zhan",           "", "1" }),
    1610 : ({ "find", "煎豆腐",       "jian doufu",         "", "1" }),
    1620 : ({ "find", "烧面筋",       "shao mianjin",       "", "1" }),
    2000 : ({ "find", "熏羊头",       "yang tou",           "", "1" }),
    2010 : ({ "find", "羊肉泡馍",     "pao mo",             "", "1" }),
    2020 : ({ "find", "羊肉杂碎",     "za sui",             "", "1" }),
    3010 : ({ "find", "哈密瓜",       "hami gua",           "", "1" }),
    3020 : ({ "find", "草莓",         "cao mei",            "", "1" }),
    3030 : ({ "find", "苹果",         "ping guo",           "", "1" }),
    3040 : ({ "find", "水晶葡萄",     "pu tao",             "", "1" }),
    2080 : ({ "find", "大桃子",       "tao",                "", "1" }),
    3100 : ({ "find", "五味烧鹅",     "wuwei shaoe",        "", "1" }),
    3110 : ({ "find", "香汁蒸鸭",     "xiangzhi zhengya",   "", "1" }),
    3120 : ({ "find", "辣味牛汤",     "lawei niutang",      "", "1" }),
    3130 : ({ "find", "牛肉汤面",     "niurou tangmian",    "", "1" }),
    4010 : ({ "find", "蒸酥",         "zheng su",           "", "1" }),
    4010 : ({ "find", "肉夹馍",       "roujia mo",          "", "1" }),
    4020 : ({ "find", "糙米饭",       "caomi fan",          "", "1" }),
    4030 : ({ "find", "酱牛肉",       "jiang niurou"        "", "1" }),
    4040 : ({ "find", "菜糠团子",     "caikang tuanzi"      "", "1" }),
    4050 : ({ "find", "酒壶",         "jiuhu"               "", "1" }),
    4060 : ({ "find", "供果",         "gong guo"            "", "1" }),
    4070 : ({ "find", "小供果",       "gong guo"            "", "1" }),
    4080 : ({ "find", "菜糠团子",     "caikang tuanzi"      "", "1" }),
    4100 : ({ "find", "醉泥螺",       "zui niluo",          "", "1" }),
    4200 : ({ "find", "熏鱼",         "xun yu",             "", "1" }),
    4300 : ({ "find", "蒸螃蟹",       "zheng pangxie",      "", "1" }),
    4400 : ({ "find", "烧龙虾",       "shao longxia",       "", "1" }),
    5010 : ({ "find", "小青菜",       "xqc",                "", "1" }),
    5020 : ({ "find", "大黄瓜",       "dhg",                "", "1" }),
    5100 : ({ "find", "烤全羊",       "kao quanyang",       "", "1" }),
    5110 : ({ "find", "烤乳猪",       "kao ruzhu",          "", "1" }),
    6010 : ({ "find", "琼瑶豆腐",     "qiongyao",           "", "1" }),
    6020 : ({ "find", "油炸花生",     "hua sheng",          "", "1" }),
    6030 : ({ "find", "炒花生",       "hua sheng",          "", "1" }),
    6040 : ({ "find", "煮花生",       "hua sheng",          "", "1" }),
    6050 : ({ "find", "五香花生",     "hua sheng",          "", "1" }),
    6060 : ({ "find", "烘花生",       "hua sheng",          "", "1" }),
    6070 : ({ "find", "卤花生",       "hua sheng",          "", "1" }),
    6080 : ({ "find", "盐水花生",     "hua sheng",          "", "1" }),
    6090 : ({ "find", "细糖花生",     "hua sheng",          "", "1" }),
    6100 : ({ "find", "油炸鸡",       "youzha ji",          "", "1" }),
    6110 : ({ "find", "油豆腐",       "you doufu",          "", "1" }),
    6120 : ({ "find", "油面筋",       "you mianjin",        "", "1" }),
    6130 : ({ "find", "油糕",         "you gao",            "", "1" }),
    6140 : ({ "find", "油饼",         "you bing",           "", "1" }),
    7010 : ({ "find", "香酥",         "xiangsu",            "", "1" }),
    7020 : ({ "find", "糖糕",         "tanggao",            "", "1" }),
    7030 : ({ "find", "油食",         "youshi",             "", "1" }),
    7040 : ({ "find", "烤羊腿",       "yangtui",            "", "1" }),
    8010 : ({ "find", "桃斋果",       "zhai guo",           "", "1" }),
    8020 : ({ "find", "杏斋果",       "zhai guo",           "", "1" }),
    8030 : ({ "find", "梨斋果",       "zhai guo",           "", "1" }),
    8040 : ({ "find", "面斋果",       "zhai guo",           "", "1" }),
    8050 : ({ "find", "豆斋果",       "zhai guo",           "", "1" }),
    9000 : ({ "find", "粗瓷茶碗",     "cuci chawan",        "", "1" }),
    9010 : ({ "find", "小菜",         "xiao cai",           "", "1" }),
    9020 : ({ "find", "稀饭",         "xi fan",             "", "1" }),
    9100 : ({ "find", "五香炒豆",     "chao dou",           "", "1" }),
    9110 : ({ "find", "香瓜子",       "gua zi",             "", "1" }),
    9120 : ({ "find", "卤味干",       "luwei gan",          "", "1" }),
    9130 : ({ "find", "香油臭干",     "chou gan",           "", "1" }),
    9140 : ({ "find", "油炸干",       "youzha gan",         "", "1" }),
    9150 : ({ "find", "美味豆腐羹",   "doufu geng",         "", "1" }),
    9160 : ({ "find", "小蛋糕" ,      "dan gao",            "", "1" }),
    9170 : ({ "find", "小煎酥" ,      "jian su",            "", "1" }),
    9200 : ({ "find", "白兰瓜" ,      "bailan gua",         "", "1" }),
    9210 : ({ "find", "番木瓜" ,      "fanmu gua",          "", "1" }),
    9220 : ({ "find", "木瓜" ,        "mu gua",             "", "1" }),
    9230 : ({ "find", "柑子" ,        "gan zi",             "", "1" }),
    9240 : ({ "find", "桔子" ,        "ju zi",              "", "1" }),
    9250 : ({ "find", "柚子" ,        "you zi",             "", "1" }),
    9260 : ({ "find", "豆芽" ,        "dou ya",             "", "1" }),
    9270 : ({ "find", "花菜" ,        "hua cai",            "", "1" }),
    9280 : ({ "find", "野蘑菇" ,      "mo gu",              "", "1" }),
    9290 : ({ "find", "黑木耳" ,      "hei muer",           "", "1" }),
    9300 : ({ "find", "山笋",         "shan sun",           "", "1" }),
    9310 : ({ "find", "红苋菜",       "hong xiancai",       "", "1" }),
    9320 : ({ "find", "红茶",         "hong cha",           "", "1" }),
    9330 : ({ "find", "绿茶",         "lu cha",             "", "1" }),
    9340 : ({ "find", "水酒罐",       "jiu guan",           "", "1" }),
    9350 : ({ "find", "清白老酒壶",   "jiu hu",             "", "1" }),
    9360 : ({ "find", "瓷酒盅",       "jiu zhong",          "", "1" }),
    9500  : ({ "find", "鲜笋",        "xian sun",           "", "1" }),
    9600 : ({ "find", "蘑菇",         "mo gu" ,              "", "1" }),
    9700 : ({ "find",   "山药",         "ggsc",          "","1" }),
    9800 : ({ "find",   "黄精",         "ggsc",          "","1" }),
    9900 : ({ "find",   "石花菜",        "ggsc",          "","1" }),
   10000 : ({ "find",    "黄花菜",        "ggsc",          "","1" }),
   10100 : ({ "find",    "扁豆角",        "ggsc",          "","1" }),
   11000 : ({ "find",    "豇豆角",        "ggsc",          "","1" }),
   11500: ({ "find",     "王瓜",        "ggsc",          "","1" }),
   12000 : ({ "find",    "白果",        "ggsc",          "","1" }),
   12500 : ({ "find",    "蔓青",        "ggsc",          "","1" }),
   12700 : ({ "find",    "茄子",        "ggsc",          "","1" }),
   12800 : ({ "find",    "冬瓜",        "ggsc",          "","1" }),
   12900 : ({ "find",    "芋头",        "ggsc",          "","1" }),
   13000 : ({ "find",    "萝卜",        "ggsc",          "","1" }),
   13500 : ({ "find",    "林檎",        "ggsc",          "","1" }),
   13600 : ({ "find", "橄榄",        "ggsc",          "","1" }),
   13700 : ({ "find",    "莲肉",        "ggsc",          "","1" }),
   13800 : ({ "find",    "荔枝",        "ggsc",          "","1" }),
   13900: ({ "find", "龙眼",        "ggsc",          "","1" }),
   14000 : ({ "find",    "山栗",        "ggsc",          "","1" }),
   14200 : ({ "find",     "风菱",        "ggsc",          "","1" }),
   14300 : ({ "find",    "柿子",        "ggsc",          "","1" }),
   14400 : ({ "find",    "胡桃",        "ggsc",          "","1" }),
   15000 : ({ "find",    "银杏",        "ggsc",          "","1" }),
   15200 : ({ "find",    "金橘",        "ggsc",          "","1" }),
   15500 : ({ "find",    "香橙",        "ggsc",          "","1" }),
   20010 : ({ "find", "烤肉块",       "rou",                "", "1" }),
   20020 : ({ "find", "烤肉巴子",     "rou",                "", "1" }),
   20030 : ({ "find", "烤头肉",       "rou",                "", "1" }),
   20040 : ({ "find", "烤腿子肉",     "rou",                "", "1" }),
   20050 : ({ "find", "烤胸脯肉",     "rou",                "", "1" }),
   20060 : ({ "find", "烤坐臀肉",     "rou",                "", "1" }),
   30000 : ({ "find", "雪饮杯",       "snowglass",          "", "1" }),
   30010 : ({ "find", "油焖山笋尖",   "food",               "", "1" }),
   30020 : ({ "find", "清烧地龙衣",   "food",               "", "1" }),
   30030 : ({ "find", "炖汤蘑菇",     "food",               "", "1" }),
   30040 : ({ "find", "野栗子糕",     "food",               "", "1" }),
   30050 : ({ "find", "黑松子饼",     "food",               "", "1" }),
   30060 : ({ "find", "白果仁脆酥",   "food",               "", "1" }),
   40200 : ({ "find", "玉米馍馍",     "mo mo",              "", "1" }),
   40400 : ({ "find", "豆沙馍馍",     "mo mo",              "", "1" }),
   40600 : ({ "find", "菜馅馍馍",     "mo mo",              "", "1" }),
   40800 : ({ "find", "葱花馍馍",     "mo mo",              "", "1" }),
  100000 : ({ "find", "净瓶",         "jingping",           "", "1" }),
  200100 : ({ "find", "蛇肉",         "rou",                "", "1" }),
  200200 : ({ "find", "鹿脯",         "rou",                "", "1" }),
  200300 : ({ "find", "熊掌",         "rou",                "", "1" }),
  200400 : ({ "find", "驼峰",         "rou",                "", "1" }),
  200500 : ({ "find", "马腿",         "rou",                "", "1" }),
  200600 : ({ "find", "驴肺",         "rou",                "", "1" }),
  200700 : ({ "find", "狼肝",         "rou",                "", "1" }),
  200800 : ({ "find", "狍肉",         "rou",                "", "1" }),
  200900 : ({ "find", "虎唇",         "rou",                "", "1" }),
  201000 : ({ "find", "狮鼻",         "rou",                "", "1" }),
  201100 : ({ "find", "豹舌",         "rou",                "", "1" }),
  300100 : ({ "find", "獐子肉",       "rou",                "", "1" }),
  300200 : ({ "find", "野狸肉",       "rou",                "", "1" }),
  300300 : ({ "find", "野兔肉",       "rou",                "", "1" }),
  300400 : ({ "find", "野羊肉",       "rou",                "", "1" }),
  300500 : ({ "find", "野鹿肉",       "rou",                "", "1" }),
  300600 : ({ "find", "野鸡肉",       "rou",                "", "1" }),
  300700 : ({ "find", "狍子肉",       "rou",                "", "1" }),
  300800 : ({ "find", "蟒蛇肉",       "rou",                "", "1" }),
  300900 : ({ "find", "狼肉",         "rou",                "", "1" }),
  301000 : ({ "find", "豹肉",         "rou",                "", "1" }),
  301100 : ({ "find", "虎肉",         "rou",                "", "1" }),
  301200 : ({ "find", "鹫肉",         "rou",                "", "1" }),
  301300 : ({ "find", "狮肉",         "rou",                "", "1" }),
  400010 : ({ "find", "米饭",         "mi fan",             "", "1" }),
  400020 : ({ "find", "面筋",         "mian jin",           "", "1" }),
  700100 : ({ "find", "山驼肉干",     "rou",                "", "1" }),
  700110 : ({ "find", "树鸦肉干",     "rou",                "", "1" }),
  702120 : ({ "find", "猩猩肉条",     "rou",                "", "1" }),
  703010 : ({ "find", "山鼠肉饼",     "rou",                "", "1" }),
 1000070 : ({ "find", "熊掌",         "xiong zhang",        "", "1" }),
 1000080 : ({ "find", "猩唇",         "xing chun",          "", "1" }),
]);

void create()
{
  seteuid(getuid());
  m_keys=order_list(keys(quests_food));
}

mapping query_quest(object who)
{
  mapping quest;
  int i;
  string* info;
  string *strs = ({
    "$N想想说道：今天我正准备请人去找",
    "$N细想了一下说道：本门有人想要什么",
    "$N点头说道：这里尚缺些",
    "$N想想说道：可否帮本门寻得",
  });  
  
  i = quest_accurate_index (m_keys, who->query("combat_exp"));
  i = quest_random_index (m_keys, i);
  info=quests_food[m_keys[i]];
  
  quest=(["quest":"找"+info[IDX_NAME]]);
  quest+=(["quest_msg":strs[random(sizeof(strs))]+info[IDX_NAME]+
           "，你可否去寻一些来？\n"]);
  quest+=(["bonus":log10(who->query("combat_exp"))*40+10]);
  quest+=(["reward_msg":"$N笑道：不错不错，有劳你了。\n"]);
  return quest;
}