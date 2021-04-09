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
1	:	({"短叉",({"duan cha","cha","fork"}),}),
3	:	({"长叉",({"chang cha","cha","fork"}),}),
5	:	({"银叉",({"yin cha","cha","fork"}),}),
7	:	({"虎头叉",({"hutou cha","cha","fork"}),}),
9	:	({"花叉",({"hua cha","cha","fork"}),}),
11	:	({"金叉",({"jin cha","cha","fork"}),}),
13	:	({"双头叉",({"shuangtou cha","cha","fork"}),}),
15	:	({"飞雷叉",({"feilei cha","cha","fork"}),}),
17	:	({"蛇矛叉",({"shemao cha","cha","fork"}),}),
19	:	({"刺画叉",({"cihua cha","cha","fork"}),}),
21	:	({"金蛟叉",({"jinjiao cha","cha","fork"}),}),
23	:	({"吐信叉",({"tuxin cha","cha","fork"}),}),
25	:	({"百花叉",({"baihua cha","cha","fork"}),}),
27	:	({"玲珑叉",({"linglong cha","cha","fork"}),}),
29	:	({"铁钩叉",({"tiegou cha","cha","fork"}),}),
32	:	({"行龙叉",({"xinglong cha","cha","fork"}),}),
35	:	({"迎风叉",({"yingfeng cha","cha","fork"}),}),
37	:	({"虎牙叉",({"huya cha","cha","fork"}),}),
40	:	({"碧血叉",({"bixue cha","cha","fork"}),}),
43	:	({"涯角叉",({"yajiao cha","cha","fork"}),}),
46	:	({"双刃叉",({"shuangren cha","cha","fork"}),}),
49	:	({"飞翼叉",({"feiyi cha","cha","fork"}),}),
52	:	({"曲刃叉",({"quren cha","cha","fork"}),}),
55	:	({"虎威叉",({"huwei cha","cha","fork"}),}),
58	:	({"分水叉",({"fenshui cha","cha","fork"}),}),
61	:	({"灵牙叉",({"lingya cha","cha","fork"}),}),
64	:	({"烧火叉",({"shaohuo cha","cha","fork"}),}),
67	:	({"金线叉",({"jinxian cha","cha","fork"}),}),
70	:	({"掣电叉",({"chedian cha","cha","fork"}),}),
73	:	({"五钩叉",({"wugou cha","cha","fork"}),}),
76	:	({"五虎叉",({"wuhu cha","cha","fork"}),}),
79	:	({"沥泉",({"li quan","cha","fork"}),}),
82	:	({"猿飞",({"yuan fei","cha","fork"}),}),
85	:	({"透甲",({"tou jia","cha","fork"}),}),
88	:	({"落影",({"luo ying","cha","fork"}),}),
91	:	({"裂马",({"lie ma","cha","fork"}),}),
94	:	({"乌泽",({"wu ze","cha","fork"}),}),
97	:	({"绿沉",({"lv chen","cha","fork"}),}),
100	:	({"傲血",({"ao xue","cha","fork"}),}),
105	:	({"突刺",({"tu ci","cha","fork"}),}),
110	:	({"掳魂",({"lu hun","cha","fork"}),}),
115	:	({"丈叉",({"zhang cha","cha","fork"}),}),
120	:	({"银筘叉",({"yinkou cha","cha","fork"}),}),
125	:	({"火龙叉",({"huolong cha","cha","fork"}),}),
130	:	({"横江叉",({"hengjiang cha","cha","fork"}),}),
135	:	({"巡海叉",({"xunhai cha","cha","fork"}),}),
140	:	({"沉舟叉",({"chenzhou cha","cha","fork"}),}),
145	:	({"炼石叉",({"lianshi cha","cha","fork"}),}),
150	:	({"大海无量",({"wu liang","cha","fork"}),}),
155	:	({"水母",({"shui mu","cha","fork"}),}),
160	:	({"离心",({"li xin","cha","fork"}),}),
161	:	({"百利",({"bai li","cha","fork"}),}),
162	:	({"出云",({"chu yun","cha","fork"}),}),
163	:	({"八蛭",({"ba zhi","cha","fork"}),}),
164	:	({"九鲤",({"jiu li","cha","fork"}),}),
165	:	({"百螭",({"bai li","cha","fork"}),}),
167	:	({"弱水三千",({"ruo shui","cha","fork"}),}),
169	:	({"九子相交",({"jiu zi","cha","fork"}),}),
170	:	({"勾心斗角",({"dou jiao","cha","fork"}),}),
]);
}

void create()
{
	set_name("武器◆叉",({"fork"}));
	set("skill_type","fork");
	set("unit","根");
	setup();
}