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
1	:	({"木槌",({"mu chui","chui","hammer"}),}),
3	:	({"木锤",({"mu chui","chui","hammer"}),}),
5	:	({"铁锤",({"tie chui","chui","hammer"}),}),
7	:	({"镔铁锤",({"bintie chui","chui","hammer"}),}),
9	:	({"雕花铁锤",({"diaohua tiechui","chui","hammer"}),}),
11	:	({"金瓜",({"jin gua","chui","hammer"}),}),
13	:	({"梅花锤",({"meihua chui","chui","hammer"}),}),
15	:	({"八棱梅花锤",({"baleng meihua chui","chui","hammer"}),}),
17	:	({"亮银锤",({"liangyin chui","chui","hammer"}),}),
19	:	({"八棱亮银锤",({"baleng liangyin chui","chui","hammer"}),}),
21	:	({"狼牙锤",({"langya chui","chui","hammer"}),}),
23	:	({"三丁三才锤",({"sancai hammer","chui","hammer"}),}),
25	:	({"五虎五行锤",({"wuxing hammer","chui","hammer"}),}),
27	:	({"六阳六气锤",({"liuqi hammer","chui","hammer"}),}),
29	:	({"纯钩",({"chun gou","chui","hammer"}),}),
31	:	({"淳钧",({"chun jun","chui","hammer"}),}),
34	:	({"燕支",({"yan zhi","chui","hammer"}),}),
37	:	({"蔡愉",({"cai yu","chui","hammer"}),}),
40	:	({"惊鲵",({"jing ni","chui","hammer"}),}),
43	:	({"灭魂",({"mie hun","chui","hammer"}),}),
46	:	({"却邪",({"que xie","chui","hammer"}),}),
49	:	({"真刚",({"zhen gang","chui","hammer"}),}),
52	:	({"神龟",({"shen gui","chui","hammer"}),}),
55	:	({"八服",({"ba fu","chui","hammer"}),}),
58	:	({"照胆",({"zhao dan","chui","hammer"}),}),
61	:	({"含光",({"han guang","chui","hammer"}),}),
64	:	({"镇岳",({"zhen yue","chui","hammer"}),}),
67	:	({"天干",({"tian gan","chui","hammer"}),}),
70	:	({"冰魄",({"bing po bao","chui","hammer"}),}),
73	:	({"清净",({"qing jing","chui","hammer"}),}),
76	:	({"不争",({"bu zheng","chui","hammer"}),}),
79	:	({"霞飞",({"xia fei","chui","hammer"}),}),
82	:	({"觉云",({"jue yun","chui","hammer"}),}),
85	:	({"万师",({"wan shi","chui","hammer"}),}),
88	:	({"破甲",({"po jia","chui","hammer"}),}),
91	:	({"巨灵",({"ju lingi","chui","hammer"}),}),
94	:	({"烈焰",({"lie yan","chui","hammer"}),}),
97	:	({"雷神",({"lei shen","chui","hammer"}),}),
100	:	({"九瓣莲花",({"jiuban lianhua","chui","hammer"}),}),
105	:	({"鬼王蚀日",({"guiwang shiri","chui","hammer"}),}),
110	:	({"狂澜碎岳",({"kuanglan suiyue","chui","hammer"}),}),
115	:	({"玄天神木",({"shen mu","chui","hammer"}),}),
120	:	({"狂澜碎岳",({"sui yue","chui","hammer"}),}),
125	:	({"磐龙破魔",({"po mo","chui","hammer"}),}),
130	:	({"空舞银电",({"kong wu","chui","hammer"}),}),
135	:	({"梦华天蛇",({"tian she","chui","hammer"}),}),
140	:	({"翻江倒海",({"jiang hai","chui","hammer"}),}),
145	:	({"十万大山",({"da shan","chui","hammer"}),}),
150	:	({"霞光万丈",({"xia guang","chui","hammer"}),}),
155	:	({"血纹重山",({"chong shan","chui","hammer"}),}),
160	:	({"周天星宿",({"xing xiu","chui","hammer"}),}),
163	:	({"斗转星移",({"xing dou","chui","hammer"}),}),
166	:	({"九霄息壤",({"xi rang","chui","hammer"}),}),
169	:	({"混元翻斗",({"hun yuan","chui","hammer"}),}),
170	:	({"混沌一气",({"hun dun","chui","hammer"}),}),
]);
}

void create()
{
	set_name("武器◆锤",({"hammer"}));
	set("skill_type","hammer");
	set("unit","把");
	setup();
}