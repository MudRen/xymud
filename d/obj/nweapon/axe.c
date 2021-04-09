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
1	:	({"铁斧",({"tie fu","axe","fu"}),}),
4	:	({"车轮斧",({"chelun fu","axe","fu"}),}),
7	:	({"鸦项斧",({"yaxiang fu","axe","fu"}),}),
10	:	({"双刃斧",({"shuangren fu","axe","fu"}),}),
13	:	({"钢刃斧",({"gangren fu","axe","fu"}),}),
16	:	({"开山斧",({"kaishan fu","axe","fu"}),}),
19	:	({"劈山斧",({"pishan fu","axe","fu"}),}),
20	:	({"长柯斧",({"changke fu","axe","fu"}),}),
23	:	({"鱼尾斧",({"yuwei fu","axe","fu"}),}),
27	:	({"鬼头斧",({"guitou fu","axe","fu"}),}),
29	:	({"凤头斧",({"fengtou fu","axe","fu"}),}),
30	:	({"混元斧",({"hunyuan fu","axe","fu"}),}),
33	:	({"九齿斧",({"jiuchi fu","axe","fu"}),}),
36	:	({"宣花斧",({"xuanhua fu","axe","fu"}),}),
39	:	({"曲月斧",({"quyue fu","axe","fu"}),}),
40	:	({"刑天斧",({"xingtian fu","axe","fu"}),}),
44	:	({"偃月斧",({"yanyue fu","axe","fu"}),}),
48	:	({"螯锯斧",({"aoju fu","axe","fu"}),}),
50	:	({"日华斧",({"rihua fu","axe","fu"}),}),
54	:	({"破军斧",({"pojun fu","axe","fu"}),}),
58	:	({"丧门斧",({"sangmen fu","axe","fu"}),}),
60	:	({"镰斧",({"lianfu","axe","fu"}),}),
64	:	({"碎颅斧",({"suilu fu","axe","fu"}),}),
68	:	({"贯甲斧",({"guanjia fu","axe","fu"}),}),
70	:	({"裂山斧",({"lieshan fu","axe","fu"}),}),
74	:	({"寒铁斧",({"hantie fu","axe","fu"}),}),
78	:	({"破虏",({"po lu","axe","fu"}),}),
80	:	({"百裂斧",({"bailie fu","axe","fu"}),}),
84	:	({"定山斧",({"dingshan fu","axe","fu"}),}),
88	:	({"奋勇斧",({"fenyong fu","axe","fu"}),}),
90	:	({"月轮斧",({"yuelun fu","axe","fu"}),}),
94	:	({"神工斧",({"shengong fu","axe","fu"}),}),
98	:	({"五丁开山",({"wuding kai shan","axe","fu"}),}),
100	:	({"冰夷斧",({"bingyi fu","axe","fu"}),}),
103	:	({"摄月斧",({"sheyue fu","axe","fu"}),}),
106	:	({"武冠斧",({"wuguan fu","axe","fu"}),}),
109	:	({"乌云斧",({"wuyun fu","axe","fu"}),}),
110	:	({"碎岳",({"sui yue","axe","fu"}),}),
113	:	({"祭神",({"ji shen","axe","fu"}),}),
116	:	({"苍龙斧",({"canglong fu","axe","fu"}),}),
119	:	({"拒马斧",({"juma fu","axe","fu"}),}),
120	:	({"伐桂",({"fa gui","axe","fu"}),}),
123	:	({"裂魂",({"lie hun","axe","fu"}),}),
125	:	({"太阴斧",({"taiyin fu","axe","fu"}),}),
128	:	({"万征斧",({"wanzheng fu","axe","fu"}),}),
130	:	({"紫金巨斧",({"zijin jufu","axe","fu"}),}),
133	:	({"玄火重",({"xuanhuo zhong","axe","fu"}),}),
135	:	({"鬼王斧",({"guiwang fu","axe","fu"}),}),
138	:	({"削金斧",({"xiaojin fu","axe","fu"}),}),
140	:	({"火云斧",({"huoyun fu","axe","fu"}),}),
145	:	({"凭虚斧",({"pingxu fu","axe","fu"}),}),
150	:	({"雷公斧",({"leigong fu","axe","fu"}),}),
155	:	({"提颅斧",({"tilu fu","axe","fu"}),}),
160	:	({"开天斧",({"kaitian fu","axe","fu"}),}),
163	:	({"庚金巨斩",({"gengjin juzhan","axe","fu"}),}),
165	:	({"恨天地合",({"hen tiandihe","axe","fu"}),}),
168	:	({"千岁巫骨",({"qiansui wugu","axe","fu"}),}),
170	:	({"混沌一破",({"hundun yipo","axe","fu"}),}),
]);
}

void create()
{
	set_name("武器◆斧",({"axe"}));
	set("skill_type","axe");
	set("unit","把");
	setup();
}

/*
mapping w_title(){
		return ([
"吴刚"  : ({"strength","spells","axe"}),
"程咬金": ({"karma","karma","axe"}),
"樊哙"  : ({"courage","strength","axe"}),
"颜良"  : ({"composure","strength","axe"}),
"愚公"  : ({"courage","composure","axe"}),
"鲁班"  : ({"constitution","intelligence","ad_axe"}),
"蒙恬"  : ({"intelligence","strength","ad_axe"}),
"文丑"  : ({"personality","strength","ad_axe"}),
"沉香"  : ({"karma","spirituality","axe"}),
"夏侯渊": ({"strength","strength","axe"}),
"夏侯敦": ({"courage","courage","axe"}),
"甘宁"  : ({"spirituality","spirituality","axe"}),
"钟馗"  : ({"composure","composure","ad_axe"}),
"蚩尤"  : ({"axe","axe","axe"}),
"盘古"  : ({"ad_axe","ad_axe","ad_axe"}),
]);
}
*/