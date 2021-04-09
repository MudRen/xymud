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
1	:	({"桃木剑",({"taomu jian","jian","sword"}),}),
3	:	({"抱朴剑",({"baopu jian","jian","sword"}),}),
5	:	({"柳绵剑",({"liumian jian","jian","sword"}),}),
7	:	({"辟谷剑",({"bigu jian","jian","sword"}),}),
9	:	({"坐忘剑",({"zuowang jian","jian","sword"}),}),
11	:	({"烛泪剑",({"zhulei jian","jian","sword"}),}),
13	:	({"棠溪剑",({"tangxi jian","jian","sword"}),}),
15	:	({"秀霸",({"xiu ba","jian","sword"}),}),
17	:	({"玉具剑",({"yuju jian","jian","sword"}),}),
19	:	({"龙彩",({"long cai","jian","sword"}),}),
21	:	({"孟德",({"meng de","jian","sword"}),}),
23	:	({"思召",({"si zhao","jian","sword"}),}),
25	:	({"倚天",({"yi tian","jian","sword"}),}),
27	:	({"飞星",({"fei xing","jian","sword"}),}),
29	:	({"流采",({"liu cai","jian","sword"}),}),
31	:	({"华铤",({"hua ting","jian","sword"}),}),
33	:	({"白虹",({"bai hong","jian","sword"}),}),
35	:	({"紫电",({"zi dian","jian","sword"}),}),
37	:	({"辟邪",({"bi xie","jian","sword"}),}),
39	:	({"流星",({"liu xing","jian","sword"}),}),
41	:	({"青冥",({"qing ming","jian","sword"}),}),
43	:	({"百里",({"bai li","jian","sword"}),}),
45	:	({"大吴",({"da wu","jian","sword"}),}),
47	:	({"流光",({"liu guang","jian","sword"}),}),
49	:	({"步光",({"bu guang","jian","sword"}),}),
51	:	({"腾空剑",({"tengkong jian","jian","sword"}),}),
53	:	({"夏禹剑",({"xiayu jian","jian","sword"}),}),
55	:	({"夏启剑",({"xiaqi jian","jian","sword"}),}),
57	:	({"胜邪",({"sheng xie","jian","sword"}),}),
59	:	({"工布",({"gong bu","jian","sword"}),}),
61	:	({"磐郢",({"pan ying","jian","sword"}),}),
63	:	({"湛卢",({"zhan lu","jian","sword"}),}),
65	:	({"鱼肠",({"yu chang","jian","sword"}),}),
67	:	({"蟠钢",({"pan gang","jian","sword"}),}),
69	:	({"松纹",({"song wen","jian","sword"}),}),
71	:	({"巨阙",({"ju que","jian","sword"}),}),
73	:	({"纯钧",({"chun jun","jian","sword"}),}),
75	:	({"画影",({"hua ying","jian","sword"}),}),
77	:	({"腾空",({"teng kong","jian","sword"}),}),
79	:	({"太康",({"tai kang","jian","sword"}),}),
81	:	({"夹剑",({"jia jian","jian","sword"}),}),
83	:	({"定光",({"ding guang","jian","sword"}),}),
85	:	({"昆吾",({"kun wu","jian","sword"}),}),
87	:	({"骏剑",({"jun jian","jian","sword"}),}),
89	:	({"干将",({"gan jiang","jian","sword"}),}),
91	:	({"湛卢",({"zhan lu","jian","sword"}),}),
93	:	({"胜邪",({"sheng xie","jian","sword"}),}),
95	:	({"鱼肠",({"yu chang","jian","sword"}),}),
97	:	({"长阙",({"chang que","jian","sword"}),}),
99	:	({"掩日",({"yan ri","jian","sword"}),}),
101	:	({"断水",({"duan shui","jian","sword"}),}),
105	:	({"转魄",({"zhuan po","jian","sword"}),}),
110	:	({"悬翦",({"xuan jian","jian","sword"}),}),
115	:	({"龙渊",({"long yuan","jian","sword"}),}),
120	:	({"太阿",({"tai a","jian","sword"}),}),
125	:	({"定秦",({"ding qin","jian","sword"}),}),
130	:	({"赤霄",({"chi xiao","jian","sword"}),}),
135	:	({"茂陵剑",({"maoling jian","jian","sword"}),}),
140	:	({"太常",({"tai chang","jian","sword"}),}),
145	:	({"阖闾",({"he lv","jian","sword"}),}),
150	:	({"兰叶",({"lan ye","jian","sword"}),}),
155	:	({"青萍",({"qing ping","jian","sword"}),}),
160	:	({"乘胜万里伏",({"chengsheng wanli fu","jian","sword"}),}),
163	:	({"更国更始",({"gengguo gengshi","jian","sword"}),}),
166	:	({"沉水龙雀",({"chenshui longque","jian","sword"}),}),
169	:	({"大夏龙雀",({"daxia longque","jian","sword"}),}),
170	:	({"四尺千金",({"sichi qianjin","jian","sword"}),}),
]);
}

void create()
{
	set_name("武器◆剑",({"sword"}));
	set("skill_type","sword");
	set("unit","把");
	setup();
}