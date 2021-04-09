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
1	:	({"拂尘",({"fuchen","bian","whip","suo"}),}),
4	:	({"妙手拂",({"miaoshou fu","bian","whip","suo"}),}),
7	:	({"仙子带",({"xianzi dai","bian","whip","suo"}),}),
10	:	({"辟邪拂",({"bixie fu","bian","whip","suo"}),}),
13	:	({"幻彩带",({"huancai dai","bian","whip","suo"}),}),
14	:	({"天蚕索",({"tiancan suo","bian","whip","suo"}),}),
17	:	({"罗刹索",({"luosha suo","bian","whip","suo"}),}),
20	:	({"缚神索",({"fushen suo","bian","whip","suo"}),}),
23	:	({"彩虹带",({"caihong dai","bian","whip","suo"}),}),
25	:	({"流云带",({"liuyun dai","bian","whip","suo"}),}),
27	:	({"碧波索",({"bibo suo","bian","whip","suo"}),}),
30	:	({"太乙拂",({"taiyi fu","bian","whip","suo"}),}),
33	:	({"乾坤带",({"qiankun dai","bian","whip","suo"}),}),
36	:	({"如意带",({"ruyi dai","bian","whip","suo"}),}),
39	:	({"清心拂",({"qingxin fu","bian","whip","suo"}),}),
40	:	({"玉宝拂",({"yubao fu","bian","whip","suo"}),}),
43	:	({"伏魔索",({"fumo suo","bian","whip","suo"}),}),
46	:	({"碧玉索",({"biyu suo","bian","whip","suo"}),}),
49	:	({"回春拂",({"huichun fu","bian","whip","suo"}),}),
50	:	({"松香拂",({"songxiang fu","bian","whip","suo"}),}),
53	:	({"清蕊拂",({"qingrui fu","bian","whip","suo"}),}),
56	:	({"明悟拂",({"mingwu fu","bian","whip","suo"}),}),
59	:	({"观心拂",({"guanxin fu","bian","whip","suo"}),}),
60	:	({"生露拂",({"shenglu fu","bian","whip","suo"}),}),
63	:	({"梦云拂",({"mengyun fu","bian","whip","suo"}),}),
65	:	({"行道拂",({"xingdao fu","bian","whip","suo"}),}),
67	:	({"天逸拂",({"tianyi fu","bian","whip","suo"}),}),
69	:	({"三星拂",({"sanxing fu","bian","whip","suo"}),}),
70	:	({"紫烟拂",({"ziyan fu","bian","whip","suo"}),}),
73	:	({"归云拂",({"guiyun fu","bian","whip","suo"}),}),
75	:	({"瑞霞带",({"ruixia dai","bian","whip","suo"}),}),
77	:	({"川贝拂",({"chuanbei fu","bian","whip","suo"}),}),
79	:	({"龙葵拂",({"longkui fu","bian","whip","suo"}),}),
80	:	({"乌茜拂",({"wuqian fu","bian","whip","suo"}),}),
85	:	({"连翘拂",({"lianqiao fu","bian","whip","suo"}),}),
90	:	({"枸杞拂",({"gouji fu","bian","whip","suo"}),}),
95	:	({"合欢拂",({"hehuan fu","bian","whip","suo"}),}),
100	:	({"银杏拂",({"yinxing fu","bian","whip","suo"}),}),
105	:	({"芦荟拂",({"luhui fu","bian","whip","suo"}),}),
110	:	({"舞风拂",({"wufeng fu","bian","whip","suo"}),}),
115	:	({"紫苏拂",({"zisu fu","bian","whip","suo"}),}),
120	:	({"雪融拂",({"xuerong fu","bian","whip","suo"}),}),
125	:	({"灵芝拂",({"lingzhi fu","bian","whip","suo"}),}),
130	:	({"莫思拂",({"mosi fu","bian","whip","suo"}),}),
135	:	({"慈悲拂",({"cibei fu","bian","whip","suo"}),}),
140	:	({"愁空拂",({"choukong fu","bian","whip","suo"}),}),
145	:	({"软龙筋",({"ruanlong jin","bian","whip","suo"}),}),
150	:	({"缚龙索",({"fulong suo","bian","whip","suo"}),}),
155	:	({"银锁金铃",({"yinsuo jinling","bian","whip","suo"}),}),
160	:	({"乾坤无定",({"qiankun wuding","bian","whip","suo"}),}),
163	:	({"孤星望月",({"guxing wangyue","bian","whip","suo"}),}),
166	:	({"秋水落霞",({"qiushui luoxia","bian","whip","suo"}),}),
169	:	({"此最相思",({"cizui xiangsi","bian","whip","suo"}),}),
170	:	({"揽月摘星",({"lanyue zhaixing","bian","whip","suo"}),}),
]);
}

void create()
{
	set_name("武器◆鞭",({"whip"}));
	set("skill_type","whip");
	set("unit","条");
	setup();
}

/*
mapping w_title(){
		return ([
"麻姑": ({"strength","whip"}),
"吕洞宾": ({"intelligence","whip"}),
"嫦娥"  : ({"strength","strength","whip"}),
"何仙姑"  : ({"personality","strength","whip","whip"}),
"公孙大娘"  : ({"constitution","whip"}),
"葛洪"  : ({"composure","whip"}),
"蔡文姬"  : ({"strength","whip"}),
"韩湘子"  : ({"whip","whip"}),
"太乙真人"  : ({"strength","whip","whip"}),
"云中子"  : ({"karma","ad_whip","whip"}),
]);
}
*/