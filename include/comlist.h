#include <ansi.h>

mapping combine_list = ([
        "九彩云龙珠":					//合成物件序号(用不带颜色的物件中文名字代替)
        ({
        	"/d/sea/obj/longzhureal",		
        						//合成物件文件
        	HIC"九"HIG"彩"HIW"云"HIR"龙"HIY"珠"NOR,	
        						//合成物件
        	0,					//合成物件所需等级
        	1000,					//合成物件所需内力修为
        	1000,					//合成物件所需法力修为
        						//合成物件信息
        	HIY"$N将手中龙珠按八宫之位摆在金龙珠周围，只见几道霞光掠过，九颗龙珠居然合为一体。\n"NOR,
        						//以下为合成所需物品
        	HIY"金龙珠"NOR,		"jin longzhu",
        	HIW"银龙珠"NOR,		"yin longzhu",
        	HIR"赤龙珠"NOR,		"chi longzhu",
        	YEL"橙龙珠"NOR,		"cheng longzhu",
        	HIY"黄龙珠"NOR,		"huang longzhu",
        	HIG"绿龙珠"NOR,		"lu longzhu",
        	HIC"青龙珠"NOR,		"qing longzhu",
        	HIB"蓝龙珠"NOR,		"lan longzhu",
        	HIM"紫龙珠"NOR,		"zi longzhu"
        }) ,
        "五彩补天石":					//合成物件序号
        ({
        	"/d/obj/fivestone/rbstone",		
        						//合成物件文件
        	HIY"五"HIC"彩"HIR"补"HIG"天"HIM"石"NOR,			
        						//合成物件
        	300,					//合成物件所需等级
        	4000,					//合成物件所需内力修为
        	4000,					//合成物件所需法力修为
        						//合成物件信息
        	HIW"$N聚起所有法力，凝成一道白光注入五色灵石。\n"+
        	HIR"蛰龙赤丹发出炎炎的红光。\n"+
        	HIY"凝露黄石发出明亮的黄色光芒。\n"+
        	HIG"天灵翡翠发出的澄碧的绿光。\n"+
        	HIC"碧海蓝心发出莹莹的蓝色光芒。\n"+
        	HIM"幽冥紫晶发出幽幽的紫色光芒。\n"+
        	BLINK HIW"五色灵石终于结成一体！\n"NOR,
        						//以下为合成所需物品
        	HIC"碧海蓝心"NOR,		"blue stone",
        	HIY"凝露黄石"NOR,		"yellow stone",
        	HIG"天灵翡翠"NOR,		"green stone",
        	MAG"幽冥紫晶"NOR,		"purple stone",
        	HIR"蛰龙赤丹"NOR,		"red stone",
        }) ,
        "七彩神石":					//合成物件序号
        ({
        	"/d/obj/combine/7stone/7stone",		//合成物件文件
        	HIR"七"HIM"彩"HIC"神"HIY"石"NOR,			
        						//合成物件
        	100,					//合成物件所需等级
        	2000,					//合成物件所需内力修为
        	2000,					//合成物件所需法力修为
        						//合成物件信息
        	HIC"$N将手中的七色神石摆在一起，缓缓注入法力，只见几道霞光掠过，七色神石居然合为一体。\n"NOR,
        						//以下为合成所需物品
        	HIB"蓝色神石"NOR,		"blue stone",
        	HIG"绿色神石"NOR,		"green stone",
        	HIY"金色神石"NOR,		"gold stone",
        	HIW"银色神石"NOR,		"silver stone",
        	HIM"紫色神石"NOR,		"magenta stone",
        	HIC"青色神石"NOR,		"cyan stone",
        	HIR"红色神石"NOR,		"red stone",
        }) ,
        "苍穹之星":					//合成物件序号
        ({
        	"/d/obj/combine/12xz/12xz",		//合成物件文件
        	HIW"苍穹之星"NOR,			
        						//合成物件
        	100,					//合成物件所需等级
        	2000,					//合成物件所需内力修为
        	2000,					//合成物件所需法力修为
        						//合成物件信息
        	HIC"$N将手中的12星座摆在一起，缓缓注入法力，只见几道霞光掠过，十二星座居然合为一体。\n"NOR,
        						//以下为合成所需物品
        	"天秤星",		"tian cheng",
        	"天蝎星",		"tian xie",
        	"水瓶星",		"shui ping",
        	"双子星",		"shuang zi",
        	"双鱼星",		"shuang yu",
        	"狮子星",		"shi zi",
        	"射手星",		"she shou",
        	"巨蟹星",		"ju xie",
        	"处女星",		"chu nv",
        	"金牛星",		"jin niu",
        	"白羊星",		"bai yang",
        	"摩羯星",		"mo jie",
        }) ,
        "万寿灵玉":					//合成物件序号
        ({
        	"/d/obj/combine/12sx/12sx",		//合成物件文件
        	HIY"万寿灵玉"NOR,			
        						//合成物件
        	100,					//合成物件所需等级
        	2000,					//合成物件所需内力修为
        	2000,					//合成物件所需法力修为
        						//合成物件信息
        	HIC"$N将手中的12生肖摆在一起，缓缓注入法力，只见几道霞光掠过，十二生肖居然合为一体。\n"NOR,
        						//以下为合成所需物品
        	"子鼠灵玉",		"shu lingyu",
        	"丑牛灵玉",		"niu lingyu",
        	"寅虎灵玉",		"hu lingyu",
        	"卯兔灵玉",		"tu lingyu",
        	"辰龙灵玉",		"long lingyu",
        	"巳蛇灵玉",		"she lingyu",
        	"午马灵玉",		"ma lingyu",
        	"未羊灵玉",		"yang lingyu",
        	"申猴灵玉",		"hou lingyu",
        	"天狗灵玉",		"gou lingyu",
        	"花猪灵玉",		"zhu lingyu",
        	"酉鸡灵玉",		"ji lingyu",
        }) ,
]);

mapping comskill_list = ([
        "岁寒三友":					//合成技能序号(用不带颜色的物件中文名字代替)
        ({
        	"/d/sea/obj/longzhureal",		
        						//合成技能文件
        	HIC"岁寒三友"NOR,	
        						//合成技能名称
        	0,					//合成技能所需等级
        	1000,					//合成技能所需内力修为
        	1000,					//合成技能所需法力修为
        						//合成技能信息
        	HIY"$N将手中龙珠按八宫之位摆在金龙珠周围，只见几道霞光掠过，九颗龙珠居然合为一体。\n"NOR,
        						//以下为合成所需技能和等级
        	"zhu-sword",		100,
        	"song-sword",		100,
        	"mei-sword",		100
        }) ,
]);