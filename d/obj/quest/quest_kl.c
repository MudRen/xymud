//Cracked by Roath
inherit F_CLEAN_UP;
#include <ansi.h>
#include <quest.h>

mapping quests_armor = ([
      10 : ({ "find", HIW"白术" NOR,   "baishu",          "", "1" }),
      15 : ({ "find", HIC"断续"NOR,    "duanxu"           "", "1" }),
      20 : ({ "find", HIR"红花"NOR,    "honghua",     "", "1" }),
      30 : ({ "find", HIG"莲子"NOR,    "lianzi",           "", "1" }),
      40 : ({ "find", RED"穿山甲"NOR,   "chuanshan jia",      "", "1" }),
      50 : ({ "find", HIY"杏仁"NOR,     "xingren",       "", "1" }),
     100 : ({ "find", HIC"贝母"NOR,     "bei mu",              "", "1" }),
     110 : ({ "find", HIB"独活"NOR,     "du huo",              "", "1" }),
     200 : ({ "find", YEL"川花椒"NOR,      "chuan huajiao",            "", "1" }),
    4100 : ({ "find", MAG"灵仙"NOR,     "ling xian",       "", "1" }),
    4200 : ({ "find", WHT"生地"NOR,     "shengdi",         "", "1" }),
    4300 : ({ "find", HIR"熊胆"NOR,     "xiongdan",            "", "1" }),
    4400 : ({ "find", HIW"冰片"NOR,     "bingpian",            "", "1" }),
    4450 : ({ "find", GRN"儿花"NOR,     "ercha",             "", "1" }),
    4500 : ({ "find", YEL"黄柏"NOR,      "huang bo",       "", "1" }),
    4600 : ({ "find", HIG"灵芝"NOR,      "lingzhi",      "", "1" }),
    7000 : ({ "find", CYN"生龙骨"NOR,    "shenglong gu",         "", "1" }),
    8000 : ({ "find", RED"血竭"NOR,      "xuejie",         "", "1" }),
    8100 : ({ "find", HIC"薄荷"NOR,      "bo he",        "", "1" }),
    8200 : ({ "find", HIB"防风"NOR,      "fang feng",           "", "1" }),
    8300 : ({ "find", YEL"黄连"NOR,     "huanglian",    "", "1" }),
    8400 : ({ "find", HIY"鹿茸"NOR,     "lurong",           "", "1" }),
    8500 : ({ "find", YEL"麝香"NOR,     "she xiang",         "", "1" }),
    9000 : ({ "find", HIW"雪莲"NOR,     "xuelian",                 "", "1" }),
   11500 : ({ "find", GRN"虎骨酒"NOR,     "hugu jiu",              "", "1" }),
   22000 : ({ "find", MAG"三才封髓丹"NOR, "sancai dan",         "", "1" }),
   23000 : ({ "find", "[1;32m人[33m参[35m再[36m造[37m丸[m", "zaizao wan",         "", "1" }),
   32500 : ({ "find", HIG"琥珀多寐丸"NOR,  "duomei wan",          "", "1" }),
   33000 : ({ "find", HIG"清心解毒丸"NOR,  "qingxin wan",        "", "1" }),
   33500 : ({ "find", HIG"三花九子膏"NOR,  "sanhua gao",       "", "1" }),
   34000 : ({ "find", HIC"青黛"NOR,         "qing dai",       "", "1" }),
   34500 : ({ "find", HIM"蝎粉"NOR,         "xiefen",      "", "1" }),
   35000 : ({ "find", HIW"乳香"NOR,      "ru xiang",       "", "1" }),
   35500 : ({ "find", "西洋剑",         "west sword",      "", "1" }),
   36000 : ({ "find", HIW"狗不理"NOR,   "baozi",        "", "1" }),
   36500 : ({ "find", "[1;33m小虾米[m", "xiao xiami",       "", "1" }),
   37000 : ({ "find", "[31m小鱼苗[m",  "xiao yumiao",        "", "1" }),
   37500 : ({ "find", "[32m鲶鱼[m",    "nian yu",       "", "1" }),
   40000 : ({ "find", HIY"护法袈裟"NOR, "jia sha",            "", "1" }),
   41000 : ({ "find", HIY"袈裟"NOR,     "jia sha",            "", "1" }),
   41500 : ({ "find", BLK"黑芝麻汤圆"NOR,"blackty",          "", "1" }),
   47000 : ({ "find", "[1;36m金鱼[m",  "jin yu",          "", "1" }),
   48000 : ({ "find", "[36m草鱼[m",    "cao yu",         "", "1" }),
  200000 : ({ "find", "青玉琵琶",         "pi pa",             "", "1" }),
  210000 : ({ "find", HIC"凤月刀"NOR,     "fengyue dao",          "", "1" }),
  220000 : ({ "find", YEL"古铜兽炉"NOR,   "shou lu",       "", "1" }),
  330000 : ({ "find",  HIW"白牡丹"NOR,    "mu dan",      "", "1" }),
  550000 : ({ "find", HIY"蟒龙袍"NOR,   "long pao",           "", "1" }),
  700000 : ({ "find", HIY"连翘"NOR,      "lian qiao",            "", "1" }),
  800000 : ({ "find", HIY "蟒龙袍" NOR, "long pao",           "", "1" }),
 2000000 : ({ "find", HIY"五彩天衣"NOR, "tian yi",            "", "1" }),
 2100000 : ({ "find", "皂罗袍",         "purple cloth",       "", "1" }),
 2200000 : ({ "find", HIY"锦镧袈裟"NOR, "jinlan jiasha",      "", "1" }),
]);

void create()
{
  seteuid(getuid());
  m_keys=order_list(keys(quests_armor));
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
  info=quests_armor[m_keys[i]];
  
  quest=(["quest":"找"+info[IDX_NAME]]);
  quest+=(["quest_msg":strs[random(sizeof(strs))]+info[IDX_NAME]+
           "，你可否去寻一些来？\n"]);
  quest+=(["bonus":log10(who->query("combat_exp"))*50+10]);
  quest+=(["reward_msg":"$N笑道：不错不错，有劳你了。\n"]);
  return quest;
}
