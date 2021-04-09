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
1	:	({"短杖",({"duan zhang","zhang","staff"}),}),
3	:	({"长杖",({"chang zhang","zhang","staff"}),}),
5	:	({"白骨禅杖",({"baigu chanzhang","zhang","staff"}),}),
7	:	({"阴云禅杖",({"yinyun chanzhang","zhang","staff"}),}),
9	:	({"缚魂禅杖",({"fuhun chanzhang","zhang","staff"}),}),
11	:	({"慑魄禅杖",({"shepo chanzhang","zhang","staff"}),}),
13	:	({"氤氲禅杖",({"yinyun chanzhang","zhang","staff"}),}),
15	:	({"勾魂禅杖",({"gouhun chanzhang","zhang","staff"}),}),
17	:	({"驭奴禅杖",({"yunu chanzhang","zhang","staff"}),}),
19	:	({"噬魂禅杖",({"shihun chanzhang","zhang","staff"}),}),
21	:	({"饮血禅杖",({"yinxue chanzhang","zhang","staff"}),}),
23	:	({"幽冥禅杖",({"youming chanzhang","zhang","staff"}),}),
25	:	({"永生禅杖",({"yongsheng chanzhang","zhang","staff"}),}),
27	:	({"藤萝禅杖",({"tengluo chanzhang","zhang","staff"}),}),
29	:	({"尺骸禅杖",({"chihai chanzhang","zhang","staff"}),}),
31	:	({"骨如禅杖",({"guru chanzhang","zhang","staff"}),}),
34	:	({"匿符禅杖",({"nifu chanzhang","zhang","staff"}),}),
37	:	({"灵知禅杖",({"lingzhi chanzhang","zhang","staff"}),}),
40	:	({"悲鸣禅杖",({"beiming chanzhang","zhang","staff"}),}),
43	:	({"千毒禅杖",({"qiandu chanzhang","zhang","staff"}),}),
46	:	({"催命禅杖",({"cuiming chanzhang","zhang","staff"}),}),
49	:	({"凤仙禅杖",({"fengxian chanzhang","zhang","staff"}),}),
52	:	({"曰贞禅杖",({"yuezhen chanzhang","zhang","staff"}),}),
55	:	({"勇果禅杖",({"yongguo chanzhang","zhang","staff"}),}),
58	:	({"梅藤禅杖",({"meiteng chanzhang","zhang","staff"}),}),
61	:	({"衔火禅杖",({"xianhuo chanzhang","zhang","staff"}),}),
64	:	({"赤疫禅杖",({"chiyi chanzhang","zhang","staff"}),}),
67	:	({"哭丧禅杖",({"kusang chanzhang","zhang","staff"}),}),
70	:	({"夺魂禅杖",({"duohun chanzhang","zhang","staff"}),}),
73	:	({"断筋禅杖",({"duanjin chanzhang","zhang","staff"}),}),
76	:	({"剔骨禅杖",({"tigu chanzhang","zhang","staff"}),}),
79	:	({"堰肩禅杖",({"yanjian chanzhang","zhang","staff"}),}),
82	:	({"锁肤禅杖",({"suofu chanzhang","zhang","staff"}),}),
85	:	({"五行禅杖",({"wuxing chanzhang","zhang","staff"}),}),
88	:	({"葬骨禅杖",({"zanggu chanzhang","zhang","staff"}),}),
91	:	({"玄狐禅杖",({"xuanhu chanzhang","zhang","staff"}),}),
94	:	({"腰斩禅杖",({"yaozhan chanzhang","zhang","staff"}),}),
97	:	({"扑天禅杖",({"putian chanzhang","zhang","staff"}),}),
100	:	({"幽量禅杖",({"youliang chanzhang","zhang","staff"}),}),
105	:	({"剪髯禅杖",({"jianran chanzhang","zhang","staff"}),}),
110	:	({"血魔禅杖",({"xuemo chanzhang","zhang","staff"}),}),
115	:	({"神行禅杖",({"shenxing chanzhang","zhang","staff"}),}),
120	:	({"绯窍禅杖",({"feiqiao chanzhang","zhang","staff"}),}),
125	:	({"因林佛骨",({"yinlin fogu","zhang","staff"}),}),
130	:	({"赤髯长杖",({"chiran changzhang","zhang","staff"}),}),
135	:	({"青藤玉树",({"qingteng yushu","zhang","staff"}),}),
140	:	({"空横苍青",({"kongheng cangqing","zhang","staff"}),}),
145	:	({"金攥摧坚",({"cui jian","zhang","staff"}),}),
150	:	({"闪电孤勇",({"shan dian","zhang","staff"}),}),
155	:	({"虬龙凤飞",({"feng fei","zhang","staff"}),}),
160	:	({"乾坤八卦",({"ba guan","zhang","staff"}),}),
163	:	({"九幽伏魔",({"fu mo","zhang","staff"}),}),
166	:	({"金刚破天",({"po tian","zhang","staff"}),}),
170	:	({"无天寂灭",({"ji mie","zhang","staff"}),}),
]);
}

void create()
{
	set_name("武器◆杖",({"staff"}));
	set("skill_type","staff");
	set("unit","根");
	setup();
}