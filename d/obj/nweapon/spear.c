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
	return ([
1	:	({"短枪",({"duan qiang","qiang","spear"}),}),
3	:	({"夷矛",({"yi mao","qiang","spear"}),}),
5	:	({"酉矛",({"you mao","qiang","spear"}),}),
7	:	({"长枪",({"chang qiang","qiang","spear"}),}),
9	:	({"银枪",({"yin qiang","qiang","spear"}),}),
11	:	({"虎头枪",({"hutou qiang","qiang","spear"}),}),
13	:	({"花枪",({"hua qiang","qiang","spear"}),}),
15	:	({"金枪",({"jin qiang","qiang","spear"}),}),
17	:	({"双头枪",({"shuangtou qiang","qiang","spear"}),}),
19	:	({"飞雷枪",({"feilei qiang","qiang","spear"}),}),
21	:	({"蛇矛",({"she mao","qiang","spear"}),}),
23	:	({"刺画枪",({"cihua qiang","qiang","spear"}),}),
25	:	({"金蛟枪",({"jinjiao qiang","qiang","spear"}),}),
27	:	({"吐信枪",({"tuxin qiang","qiang","spear"}),}),
29	:	({"拐枪",({"guai qiang","qiang","spear"}),}),
31	:	({"百花枪",({"baihua qiang","qiang","spear"}),}),
34	:	({"玲珑枪",({"linglong qiang","qiang","spear"}),}),
37	:	({"铁钩枪",({"tiegou qiang","qiang","spear"}),}),
40	:	({"行龙枪",({"xinglong qiang","qiang","spear"}),}),
43	:	({"迎风枪",({"yingfeng qiang","qiang","spear"}),}),
46	:	({"虎牙枪",({"huya qiang","qiang","spear"}),}),
49	:	({"碧血枪",({"bixue qiang","qiang","spear"}),}),
52	:	({"涯角刺",({"yajiao ci","qiang","spear"}),}),
55	:	({"双刃钩镰",({"shuangren goulian","qiang","spear"}),}),
58	:	({"飞翼枪",({"feiyi qiang","qiang","spear"}),}),
61	:	({"曲刃枪",({"quren qiang","qiang","spear"}),}),
64	:	({"虎威枪",({"huwei qiang","qiang","spear"}),}),
67	:	({"分水叉",({"fenshui cha","qiang","spear"}),}),
70	:	({"灵牙刺",({"lingya ci","qiang","spear"}),}),
73	:	({"金线枪",({"jinxian qiang","qiang","spear"}),}),
76	:	({"掣电枪",({"chedian qiang","qiang","spear"}),}),
79	:	({"五钩神枪",({"wugou shenqiang","qiang","spear"}),}),
82	:	({"五虎断魂",({"wuhu duanhun","qiang","spear"}),}),
85	:	({"沥泉",({"li quan","qiang","spear"}),}),
88	:	({"猿飞",({"yuan fei","qiang","spear"}),}),
91	:	({"透甲",({"tou jia","qiang","spear"}),}),
94	:	({"落影",({"luo ying","qiang","spear"}),}),
97	:	({"裂马",({"lie ma","qiang","spear"}),}),
100	:	({"乌泽",({"wu ze","qiang","spear"}),}),
105	:	({"绿沉",({"lv chen","qiang","spear"}),}),
110	:	({"傲血",({"ao xue","qiang","spear"}),}),
115	:	({"突刺",({"tu ci","qiang","spear"}),}),
120	:	({"掳魂",({"lu hun","qiang","spear"}),}),
125	:	({"丈八蛇矛",({"zhangba shemao","qiang","spear"}),}),
130	:	({"银筘锐矛",({"yinkou ruimao","qiang","spear"}),}),
135	:	({"火龙突",({"huo long","qiang","spear"}),}),
140	:	({"横江破",({"heng jiang","qiang","spear"}),}),
145	:	({"巡海梭",({"xun hai","qiang","spear"}),}),
150	:	({"沉舟破天",({"chen zhou","qiang","spear"}),}),
155	:	({"炼石晨星",({"lian shi","qiang","spear"}),}),
160	:	({"孤问天赐",({"gu wen","qiang","spear"}),}),
164	:	({"万朵梨花",({"li hua","qiang","spear"}),}),
168	:	({"丈八独龙",({"du long","qiang","spear"}),}),
170	:	({"银丝龙筋",({"long jin","qiang","spear"}),}),
]);
}

void create()
{
	set_name("武器◆枪",({"spear"}));
	set("skill_type","spear");
	set("unit","条");
	setup();
}