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
1	:	({"单刀",({"dan dao","dao","blade"}),}),
3	:	({"钢刀",({"gang dao","dao","blade"}),}),
5	:	({"黎刀",({"li dao","dao","blade"}),}),
7	:	({"苗刀",({"miao dao","dao","blade"}),}),
9	:	({"九环刀",({"jiuhuan dao","dao","blade"}),}),
11	:	({"马刀",({"ma dao","dao","blade"}),}),
13	:	({"腰刀",({"yao dao","dao","blade"}),}),
15	:	({"钩刀",({"gou dao","dao","blade"}),}),
17	:	({"朴刀",({"pu dao","dao","blade"}),}),
19	:	({"蜀刀",({"shu dao","dao","blade"}),}),
21	:	({"环首刀",({"huanshou dao","dao","blade"}),}),
23	:	({"弯刀",({"wan dao","dao","blade"}),}),
25	:	({"百炼刀",({"bailian dao","dao","blade"}),}),
27	:	({"眉尖刀",({"meijian dao","dao","blade"}),}),
29	:	({"乌钢刀",({"wugang dao","dao","blade"}),}),
31	:	({"蝉翼刀",({"chanyi dao","dao","blade"}),}),
33	:	({"虎头刀",({"hutou dao","dao","blade"}),}),
35	:	({"银月刀",({"yinyue dao","dao","blade"}),}),
37	:	({"六合刀",({"liuhe dao","dao","blade"}),}),
39	:	({"拙刀",({"zhuo dao","dao","blade"}),}),
41	:	({"断水",({"duan shui","dao","blade"}),}),
44	:	({"冷刃刀",({"lengren dao","dao","blade"}),}),
47	:	({"凌霜刀",({"lingshuang dao","dao","blade"}),}),
50	:	({"飞镰",({"fei lian","dao","blade"}),}),
53	:	({"镂铗",({"lou jia","dao","blade"}),}),
56	:	({"赤冶刀",({"chiye dao","dao","blade"}),}),
59	:	({"宿铁刀",({"sutie dao","dao","blade"}),}),
62	:	({"威胜刀",({"weisheng dao","dao","blade"}),}),
65	:	({"警恶刀",({"jinge dao","dao","blade"}),}),
68	:	({"殒芒",({"xun mang","dao","blade"}),}),
71	:	({"龙雀",({"long que","dao","blade"}),}),
74	:	({"紫电刀",({"zidian dao","dao","blade"}),}),
77	:	({"夜曜",({"ye yao","dao","blade"}),}),
80	:	({"银弧刀",({"yinhu dao","dao","blade"}),}),
83	:	({"古意刀",({"guyi dao","dao","blade"}),}),
86	:	({"幽劫刀",({"youjie dao","dao","blade"}),}),
89	:	({"掩日刀",({"yanri dao","dao","blade"}),}),
92	:	({"建平刀",({"jianping dao","dao","blade"}),}),
95	:	({"剔骨刀",({"tigu dao","dao","blade"}),}),
97	:	({"腾马刀",({"tengma dao","dao","blade"}),}),
100	:	({"万里伏",({"wanli fu","dao","blade"}),}),
105	:	({"鳞嘉刀",({"linjia dao","dao","blade"}),}),
110	:	({"千牛刀",({"qianniu dao","dao","blade"}),}),
115	:	({"枯骨刀",({"kugu dao","dao","blade"}),}),
120	:	({"赤龙牙",({"chilong ya","dao","blade"}),}),
125	:	({"崩霜",({"beng shuang","dao","blade"}),}),
130	:	({"七劫",({"qi jie","dao","blade"}),}),
135	:	({"九狮刀",({"jiushi dao","dao","blade"}),}),
140	:	({"弯月刀",({"wanyue dao","dao","blade"}),}),
145	:	({"鱼鳞刀",({"yulin dao","dao","blade"}),}),
150	:	({"千阙刀",({"qianque dao","dao","blade"}),}),
155	:	({"钩沉",({"gou chen","dao","blade"}),}),
160	:	({"拔山",({"ba shan","dao","blade"}),}),
161	:	({"碎梦",({"sui meng","dao","blade"}),}),
162	:	({"惊魂",({"jing hun","dao","blade"}),}),
163	:	({"赤环刀",({"chihuan dao","dao","blade"}),}),
164	:	({"新亭侯",({"xinting hou","dao","blade"}),}),
165	:	({"任侠刀",({"renxia dao","dao","blade"}),}),
166	:	({"大治刀",({"dazhi dao","dao","blade"}),}),
167	:	({"玄武",({"xuan wu","dao","blade"}),}),
168	:	({"斩妖泣血",({"zhan yao","dao","blade"}),}),
169	:	({"怒雪惊羽",({"jing yu","dao","blade"}),}),
170	:	({"雪魂琅琊",({"xue hun","dao","blade"}),}),
]);
}

void create()
{
	set_name("武器◆刀",({"blade"}));
	set("skill_type","blade");
	set("unit","把");
	setup();
}