//金色装备：有1条随机属性的装备
//蓝色装备：有3到10条随机属性的装备，属性越多，出现的概率越低		
//橙色装备：有2条随机属性的装备
//红色装备：有3条固定属性的装备，第四条属性随机，并有可能额外出现1到3条随机属性
//紫色装备：有4条固定属性的装备，第五条属性随机，并有可能额外出现1到3条随机属性				 
#include <ansi.h>
#include <weapon.h>
inherit __DIR__"newweapon.c";

mapping w_names()
{
	return  ([
1	:	({"焦木棍",({"jiaomu gun","gun","bang","stick"}),}),
3	:	({"槐木棍",({"huaimu gun","gun","bang","stick"}),}),
5	:	({"残骸棍",({"canhai gun","gun","bang","stick"}),}),
7	:	({"骷髅棍",({"kulou gun","gun","bang","stick"}),}),
9	:	({"玄铁棍",({"xuantie gun","gun","bang","stick"}),}),
11	:	({"火焰棍",({"huoyan gun","gun","bang","stick"}),}),
13	:	({"暗夜棍",({"anye gun","gun","bang","stick"}),}),
15	:	({"霹雳棍",({"pili gun","gun","bang","stick"}),}),
17	:	({"隐秘棍",({"yinmi gun","gun","bang","stick"}),}),
19	:	({"笼烟棍",({"longyan gun","gun","bang","stick"}),}),
21	:	({"灵蛇棍",({"lingshe gun","gun","bang","stick"}),}),
23	:	({"阴煞棍",({"yinsha gun","gun","bang","stick"}),}),
25	:	({"怨魂棍",({"yuanhun gun","gun","bang","stick"}),}),
27	:	({"祭魂棍",({"jihun gun","gun","bang","stick"}),}),
29	:	({"梦魇棍",({"mengyan gun","gun","bang","stick"}),}),
31	:	({"心魔棍",({"xinmo gun","gun","bang","stick"}),}),
34	:	({"黑水棍",({"heishui gun","gun","bang","stick"}),}),
37	:	({"幡冢棍",({"fanjiong gun","gun","bang","stick"}),}),
40	:	({"五浊棍",({"wuzhuo gun","gun","bang","stick"}),}),
43	:	({"兽骨棍",({"shougu gun","gun","bang","stick"}),}),
46	:	({"幽崇棍",({"youchong gun","gun","bang","stick"}),}),
49	:	({"鬼凝棍",({"guining gun","gun","bang","stick"}),}),
52	:	({"孽龙棍",({"nielong gun","gun","bang","stick"}),}),
55	:	({"森罗棍",({"senluo gun","gun","bang","stick"}),}),
58	:	({"三尸棍",({"sanshi gun","gun","bang","stick"}),}),
61	:	({"九幽棍",({"jiuyou gun","gun","bang","stick"}),}),
64	:	({"丧怨棍",({"sangyuan gun","gun","bang","stick"}),}),
67	:	({"引魂棍",({"yinhun gun","gun","bang","stick"}),}),
70	:	({"拔舌棍",({"bashe gun","gun","bang","stick"}),}),
73	:	({"孽镜棍",({"niejing gun","gun","bang","stick"}),}),
76	:	({"蒸笼棍",({"zhenglong gun","gun","bang","stick"}),}),
79	:	({"铜柱棍",({"tongzhu gun","gun","bang","stick"}),}),
82	:	({"冰山棍",({"bingshan gun","gun","bang","stick"}),}),
85	:	({"血池棍",({"xuechi gun","gun","bang","stick"}),}),
88	:	({"枉死棍",({"wangsi gun","gun","bang","stick"}),}),
91	:	({"剥皮棍",({"baopi gun","gun","bang","stick"}),}),
94	:	({"渔火棍",({"yuhuo gun","gun","bang","stick"}),}),
97	:	({"阿鼻棍",({"abi gun","gun","bang","stick"}),}),
100	:	({"寨空棍",({"zhaikong gun","gun","bang","stick"}),}),
105	:	({"无间棍",({"wujian gun","gun","bang","stick"}),}),
110	:	({"双笼棍",({"shuang long gun","gun","bang","stick"}),}),
115	:	({"寂灭棍",({"jimie gun","gun","bang","stick"}),}),
120	:	({"清风棍",({"qingfeng gun","gun","bang","stick"}),}),
125	:	({"焚欲棍",({"fenyu gun","gun","bang","stick"}),}),
130	:	({"天龙破城",({"tianlong pocheng","gun","bang","stick"}),}),
135	:	({"青阳金攥",({"qing yang","stick","bang","gun"}),}),
140	:	({"金背寒钢",({"jin bei","stick","bang","gun"}),}),
145	:	({"摧坚花板",({"hua ban","stick","bang","gun"}),}),
150	:	({"化影赤金",({"hua ying","stick","bang","gun"}),}),
155	:	({"冰玉乌龙",({"wu long","stick","bang","gun"}),}),
160	:	({"霞光天罡",({"tian gang","stick","bang","gun"}),}),
163	:	({"焦金旋风",({"xuan feng","stick","bang","gun"}),}),
169	:	({"疯魔蛮王",({"man wang","stick","bang","gun"}),}),
170	:	({"赤金阴风",({"yin feng","stick","bang","gun"}),}),
]);
}

void create()
{
	set_name("武器◆棒",({"stick"}));
	set("skill_type","stick");
	set("unit","根");
	setup();
}