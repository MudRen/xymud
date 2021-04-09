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
1	:	({"棉拳套",({"mianquan tao","hand","shou","tao","unarmed",}),}),
3	:	({"绢拳套",({"juanquan tao","hand","shou","tao","unarmed",}),}),
5	:	({"皮拳套",({"piquan tao","hand","shou","tao","unarmed",}),}),
7	:	({"青铜拳套",({"qingtong quantao","hand","shou","tao","unarmed",}),}),
9	:	({"铁拳套",({"tiequan tao","hand","shou","tao","unarmed",}),}),
11	:	({"黑革拳套",({"heige quantao","hand","shou","tao","unarmed",}),}),
13	:	({"金刚拳套",({"jingang quantao","hand","shou","tao","unarmed",}),}),
15	:	({"银丝拳套",({"yinsi quantao","hand","shou","tao","unarmed",}),}),
17	:	({"百炼拳套",({"bailian quantao","hand","shou","tao","unarmed",}),}),
19	:	({"玉石拳套",({"yushi quantao","hand","shou","tao","unarmed",}),}),
21	:	({"骨牙拳套",({"guya quantao","hand","shou","tao","unarmed",}),}),
23	:	({"精金拳套",({"jingjin quantao","hand","shou","tao","unarmed",}),}),
25	:	({"彩棉拳套",({"caimian quantao","hand","shou","tao","unarmed",}),}),
27	:	({"帛布拳套",({"bobu quantao","hand","shou","tao","unarmed",}),}),
29	:	({"鳄皮拳套",({"epi quantao","hand","shou","tao","unarmed",}),}),
31	:	({"古铜拳套",({"gutong quantao","hand","shou","tao","unarmed",}),}),
35	:	({"镔铁拳套",({"bintie quantao","hand","shou","tao","unarmed",}),}),
39	:	({"龙须拳套",({"longxu quantao","hand","shou","tao","unarmed",}),}),
43	:	({"金乌拳套",({"jinwu quantao","hand","shou","tao","unarmed",}),}),
47	:	({"银隼拳套",({"yinsun quantao","hand","shou","tao","unarmed",}),}),
51	:	({"浑阳拳套",({"hunyang quantao","hand","shou","tao","unarmed",}),}),
55	:	({"碧玉拳套",({"biyu quantao","hand","shou","tao","unarmed",}),}),
59	:	({"龙骨拳套",({"longgu quantao","hand","shou","tao","unarmed",}),}),
63	:	({"金翎拳套",({"jinling quantao","hand","shou","tao","unarmed",}),}),
67	:	({"轻云拳套",({"qingyun quantao","hand","shou","tao","unarmed",}),}),
71	:	({"密纹拳套",({"miwen quantao","hand","shou","tao","unarmed",}),}),
74	:	({"百辟拳套",({"baibi quantao","hand","shou","tao","unarmed",}),}),
77	:	({"青冥拳套",({"qingming quantao","hand","shou","tao","unarmed",}),}),
80	:	({"天罡拳套",({"tiangang quantao","hand","shou","tao","unarmed",}),}),
83	:	({"龙鳞拳套",({"longlin quantao","hand","shou","tao","unarmed",}),}),
86	:	({"英杰拳套",({"yingjie quantao","hand","shou","tao","unarmed",}),}),
89	:	({"灭魔拳套",({"miemo quantao","hand","shou","tao","unarmed",}),}),
92	:	({"悯农拳套",({"minnong quantao","hand","shou","tao","unarmed",}),}),
95	:	({"虎啸拳套",({"huxiao quantao","hand","shou","tao","unarmed",}),}),
98	:	({"慈悲拳套",({"cibei quantao","hand","shou","tao","unarmed",}),}),
101	:	({"御厄拳套",({"yue quantao","hand","shou","tao","unarmed",}),}),
104	:	({"精算拳套",({"jingsuan quantao","hand","shou","tao","unarmed",}),}),
107	:	({"渡劫拳套",({"dujie quantao","hand","shou","tao","unarmed",}),}),
120	:	({"挥毫拳套",({"huihao quantao","hand","shou","tao","unarmed",}),}),
125	:	({"通天拳套",({"tongtian quantao","hand","shou","tao","unarmed",}),}),
130	:	({"珠玑拳套",({"zhuji quantao","hand","shou","tao","unarmed",}),}),
135	:	({"牙璋凤阙",({"yazhang fengque","hand","shou","tao","unarmed",}),}),
140	:	({"烟树长门",({"yanshu changmen","hand","shou","tao","unarmed",}),}),
145	:	({"秦楼箫彻",({"qinlou xiaoche","hand","shou","tao","unarmed",}),}),
150	:	({"生平沧海",({"shengping canghai","hand","shou","tao","unarmed",}),}),
155	:	({"凤罗桐花",({"fengluo tonghua","hand","shou","tao","unarmed",}),}),
160	:	({"秋山飞瀑",({"qiushan feipu","hand","shou","tao","unarmed",}),}),
162	:	({"狂澜碎岳",({"kuanglan suiyue","hand","shou","tao","unarmed",}),}),
164	:	({"六相圆融",({"liuxiang yuanrong","hand","shou","tao","unarmed",}),}),
166	:	({"百部疏主",({"baibu shuzhu","hand","shou","tao","unarmed",}),}),
168	:	({"揽月摘星",({"lanyue zhaixing","hand","shou","tao","unarmed",}),}),
170	:	({"此最相思",({"cizui xiangsi","hand","shou","tao","unarmed",}),}),
]);
}

void create()
{
	set_name("武器◆拳",({"unarmed"}));
	set("skill_type","unarmed");
	set("unit","对");
	setup();
}