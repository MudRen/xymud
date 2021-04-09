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
1	:	({"寒木鞭",({"hanmu bian","bian","mace","jian"}),}),
3	:	({"青铜锏",({"qingtong jian","bian","mace","jian"}),}),
5	:	({"纹花锏",({"wenhua bian","bian","mace","jian"}),}),
7	:	({"黄金锏",({"huangjin bian","bian","mace","jian"}),}),
9	:	({"双瞳锏",({"shuangtong bian","bian","mace","jian"}),}),
11	:	({"勤王锏",({"qinwang bian","bian","mace","jian"}),}),
13	:	({"开山锏",({"kaishan bian","bian","mace","jian"}),}),
15	:	({"双面锏",({"shuangmian bian","bian","mace","jian"}),}),
17	:	({"恶龙锏",({"elong bian","bian","mace","jian"}),}),
19	:	({"断离锏",({"duanli bian","bian","mace","jian"}),}),
21	:	({"阴阳锏",({"yinyang bian","bian","mace"}),}),
23	:	({"九节鞭",({"jiujie bian","bian","mace"}),}),
25	:	({"占星鞭",({"zhanxing bian","bian","mace"}),}),
27	:	({"龙头鞭",({"longtou bian","bian","mace"}),}),
29	:	({"蟠龙锏",({"panlong bian","bian","mace"}),}),
31	:	({"清微鞭",({"qingwei bian","bian","mace"}),}),
34	:	({"混元锏",({"hunyuan bian","bian","mace"}),}),
37	:	({"列子鞭",({"liezi bian","bian","mace"}),}),
40	:	({"咒诀锏",({"zhoujue bian","bian","mace"}),}),
43	:	({"明月锏",({"mingyue bian","bian","mace"}),}),
46	:	({"玉骨锏",({"yugu bian","bian","mace"}),}),
49	:	({"符祝锏",({"fuzhu bian","bian","mace"}),}),
52	:	({"清秘鞭",({"qingmi bian","bian","mace"}),}),
55	:	({"七星锏",({"qixing bian","bian","mace"}),}),
58	:	({"九曲鞭",({"jiuqu mace","mace","bian"}),}),
61	:	({"筑基鞭",({"zhuji mace","mace","bian"}),}),
64	:	({"玄典鞭",({"xuandian mace","mace","bian"}),}),
67	:	({"五符鞭",({"wufu mace","mace","bian"}),}),
70	:	({"祝由鞭",({"zhuyou mace","mace","bian"}),}),
73	:	({"风雷鞭",({"fenglei mace","mace","bian"}),}),
76	:	({"厚攻鞭",({"hougong mace","mace","bian"}),}),
79	:	({"平荒鞭",({"pinghuang mace","mace","bian"}),}),
82	:	({"升玄鞭",({"shengxuan mace","mace","bian"}),}),
85	:	({"回浪鞭",({"huilang mace","mace","bian"}),}),
88	:	({"飞石鞭",({"feishi mace","mace","bian"}),}),
91	:	({"渊宗锏",({"yuanzong bian","bian","mace"}),}),
94	:	({"智通鞭",({"zhitong bian","bian","mace"}),}),
97	:	({"法恭鞭",({"fagong bian","bian","mace"}),}),
100	:	({"仙灵鞭",({"xianling bian","bian","mace"}),}),
105	:	({"神威鞭",({"shenwei bian","bian","mace"}),}),
110	:	({"冰珀",({"bing bian","bian","mace","jian"}),}),
115	:	({"胧月",({"long yue","bian","mace","jian"}),}),
120	:	({"无情",({"wu qing","bian","mace","jian"}),}),
125	:	({"月神",({"yue shen","bian","mace","jian"}),}),
130	:	({"血刃",({"xue ren","bian","mace","jian"}),}),
135	:	({"破魄",({"po po","bian","mace","jian"}),}),
140	:	({"肃魂",({"su hun","bian","mace","jian"}),}),
145	:	({"护法灭魔",({"mie mo","bian","mace","jian"}),}),
150	:	({"碧血干戚",({"gan qi","bian","mace","jian"}),}),
155	:	({"斩妖泣血",({"qi xue","bian","mace","jian"}),}),
160	:	({"业火三灾",({"ye huo","bian","mace","jian"}),}),
162	:	({"坚利侯",({"jian li","jian","mace"}),}),
164	:	({"夺命龙",({"duo ming","jian","mace"}),}),
166	:	({"流黄",({"liu huang","jian","mace"}),}),
168	:	({"结绿",({"jie lv","jian","mace"}),}),
170	:	({"五方单符",({"wu fang","jian","mace"}),}),
]);
}

void create()
{
	set_name("武器◆锏",({"mace"}));
	set("skill_type","mace");
	set("unit","对");
	setup();
}