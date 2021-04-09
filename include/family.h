// by beeby 07/27/2000

// this shared file is used at several places. 
#define W_DIR(x) "/d/city/npc/obj/"+x

mapping family_name = ([
	"方寸山三星洞":1,
        "南海普陀山":1,
        "将军府":1,
        "五庄观":1,
        "阎罗地府":0,
        "月宫":0,
        "东海龙宫":0,
        "大雪山":-1,
        "翠云山芭蕉洞":-1,
        "陷空山无底洞":-1,
        "乱石山碧波潭":-1,
        "火云洞":-1,
  	"普通百姓":0,
]);

mapping all_familys = ([
        "南海普陀山" : ([
                "skill"  : ([
                        "force"   : ({"lotusforce",}),
                        "spells"  : ({"buddhism",}),
                        "dodge"   : ({"lotusmove",}),
                        "parry"   : ({"lunhui-zhang"}),
                        "staff"   : ({"lunhui-zhang"}),
                        "unarmed" : ({"jienan-zhi",}),
                        "blade"   : ({"cibeidao",}),
                        "literate": ({0,}),
                        ]),
                "title"   : "菩萨",
                ]),
        "阎罗地府" : ([
                "skill"  : ([
                        "force"   : ({"tonsillit",}),
                        "spells"  : ({"gouhunshu",}),
                        "dodge"   : ({"ghost-steps",}),
                        "parry"   : ({"hellfire-whip"}),
                        "whip"   : ({"hellfire-whip"}),
                        "unarmed" : ({"jinghun-zhang",}),
                        "sword"   : ({"zhuihun-sword",}),
                        "stick"   : ({"kusang-bang",}),
                        "literate": ({0,}),
                        ]),
                "title"   : "鬼王",
                ]),
        "方寸山三星洞" : ([
                "skill"  : ([
                        "force"   : ({"wuxiangforce",}),
                        "spells"  : ({"dao",}),
                        "dodge"   : ({"jindouyun",}),
                        "parry"   : ({"qianjun-bang"}),
                        "unarmed" : ({"puti-zhi",}),
                        "sword"   : ({"liangyi-sword",}),
                        "stick"   : ({"qianjun-bang",}),
                        "literate": ({0,}),
                        ]),
                "title"   : "地仙",
                ]),                
        "月宫" : ([
                "skill"  : ([
                        "force"   : ({"moonforce",}),
                        "spells"  : ({"moonshentong",}),
                        "dodge"   : ({"moondance",}),
                        "parry"   : ({"snowsword"}),
                        "unarmed" : ({"baihua-zhang",}),
                        "sword"   : ({"snowsword",}),
                        "whip"    : ({"jueqingbian",}),
                        "literate": ({0,}),
                        ]),
                "title"   : "仙子",
                ]),                
        "大雪山" : ([
                "skill"  : ([
                        "force"   : ({"ningxie-force",}),
                        "spells"  : ({"dengxian-dafa",}),
                        "dodge"   : ({"xiaoyaoyou",}),
                        "parry"   : ({"bingpo-blade","bainiao-jian"}),
                        "sword"   : ({"bainiao-jian"}),
                        "blade"    : ({"bingpo-blade",}),
                        "unarmed" : ({"cuixin-zhang",}),
                        "literate": ({0,}),
                        "throwing": ({0,}),
                        ]),
                "title"   : "妖王",
                "class"   : "swordsman",
                "national": "兽族",
                ]),                
        "五庄观" : ([
                "skill"  : ([
                        "force"   : ({"zhenyuan-force",}),
                        "spells"  : ({"taiyi",}),
                        "dodge"   : ({"baguazhen",}),
                        "parry"   : ({"sanqing-jian"}),
                        "sword"   : ({"sanqing-jian"}),
                        "unarmed" : ({"wuxing-quan",}),
                        "literate": ({0,}),
                        ]),
                "title"   : "道尊",
                ]),                
        "东海龙宫" : ([
                "skill"  : ([
                        "force"   : ({"dragonforce",}),
                        "spells"  : ({"seashentong",}),
                        "dodge"   : ({"dragonstep",}),
                        "parry"   : ({"fengbo-cha"}),
                        "fork"    : ({"fengbo-cha"}),
                        "unarmed" : ({"dragonfight",}),
                        "hammer"  : ({"huntian-hammer",}),
                        "literate": ({0,}),
                        ]),
                "title"   : "龙王",
                ]),  
        "将军府" : ([
                "skill"  : ([
                        "force"   : ({"lengquan-force",}),
                        "spells"  : ({"baguazhou",}),
                        "dodge"   : ({"yanxing-steps",}),
                        "parry"   : ({"bawang-qiang"}),
                        "mace"    : ({"jinglei-mace"}),
                        "unarmed" : ({"jinghun-zhang",}),
                        "spear"   : ({"bawang-qiang",}),
                        "axe"   : ({"sanban-axe",}),
                        "literate": ({0,}),
                        ]),
                "title"   : "统帅",
                ]),                              
        "火云洞" : ([
                "skill"  : ([
                        "force"   : ({"huomoforce",}),
                        "spells"  : ({"pingtian-dafa",}),
                        "dodge"   : ({"moshenbu",}),
                        "parry"   : ({"dali-bang"}),
                        "spear"   : ({"huoyun-qiang","wuyue-spear"}),
                        "unarmed" : ({"moyun-shou",}),
                        "stick"   : ({"dali-bang",}),
                        "literate": ({0,}),
                        ]),
                "title"   : "火神",
                ]),
        "陷空山无底洞" : ([
                "skill"  : ([
                        "force"   : ({"huntian-qigong",}),
                        "spells"  : ({"yaofa",}),
                        "dodge"   : ({"lingfu-steps",}),
                        "parry"   : ({"qixiu-jian","kugu-blade"}),
                        "sword"   : ({"qixiu-jian"}),
                        "blade"    : ({"kugu-blade",}),
                        "unarmed" : ({"yinfeng-zhua",}),
                        "literate": ({0,}),
                        ]),
                "title"   : "妖王",
                "national": "兽族",
                ]),                
        "蜀山派" : ([
                "skill"  : ([
                        "force"   : ({"zixia-shengong",}),
                        "spells"  : ({"taoism",}),
                        "dodge"   : ({"sevensteps",}),
                        "parry"   : ({"mindsword","yinyue-sword","canxin-jian"}),
                        "sword"   : ({"mindsword","yinyue-sword","canxin-jian"}),
                        "whip"    : ({"yirubian",}),
                        "unarmed" : ({"hunyuan-zhang",}),
                        "literate": ({0,}),
                        ]),
                "title" : "剑客",
                "class" : "swordsman",
                ]),
        "盘丝洞" : ([
                "skill"  : ([
                        "force"   : ({"jiuyin-xinjing",}),
                        "spells"  : ({"pansi-dafa",}),
                        "dodge"   : ({"yueying-wubu",}),
                        "parry"   : ({"chixin-jian"}),
                        "whip"   : ({"yinsuo-jinling"}),
                        "unarmed" : ({"lanhua-shou",}),
                        "sword"   : ({"chixin-jian","qingxia-jian"}),
                        "qin"   : ({0,}),
                        "literate": ({0,}),
                        "zhuyan"  : ({0,}),
                        ]),
                "title"   : "媚女",
                ]),              
        "百花谷" : ([
                "skill"  : ([
                        "force"   : ({"brightjade-force",}),
                        "spells"  : ({"baihua-xianfa",}),
                        "dodge"   : ({"wuyou-steps",}),
                        "parry"   : ({"zongheng-sword"}),
                        "whip"   : ({"jueqingbian"}),
                        "unarmed" : ({"rainbow-zhi",}),
                        "sword"   : ({"zongheng-sword",}),
                        "literate": ({0,}),
                        ]),
                "title"   : "花仙",
                ]),  
               "散仙派" : ([
                "skill"  : ([
                        "force"   : ({"wuzheng-force",}),
                        "spells"  : ({"scratmancy",}),
                        "dodge"   : ({"five-avoid",}),
                        "parry"   : ({"huoyan-dao"}),
                        "blade"   : ({"pomo-blade"}),
                        "unarmed" : ({"yinyang-zhang",}),
                        "literate": ({0,}),
                        "zhanbu"  : ({0,}),
                       "bolomiduo": ({0,}),
                  "sword" : ({"qinglian-jian"}),
                        ]),
                "title"   : "炼气士",
                ]),
]);

mapping familys = ([
        "五庄观" 	: ([
        	"class"	: "xian",
        	"skills": ({	"unarmed","wuxing-quan",
				"parry","fumo-zhang",
				"dodge","baguazhen",
				"spells","taiyi",
				"force","zhenyuan-force",
				"staff","fumo-zhang",
			}),
		"weapon": W_DIR("staff"),
		]),

	"南海普陀山"	: ([
		"class"	: "xian",
		"skills": ({	"unarmed","jienan-zhi",
				"parry","lunhui-zhang",
				"dodge","lotusmove",
				"force","lotusforce",
				"spells","buddhism",
				"staff","lunhui-zhang",
			}),
		"weapon": W_DIR("staff"),
		]),

	"方寸山三星洞"	: ([
		"class" : "xian",
		"skills": ({	"unarmed","puti-zhi",
				"parry","qianjun-bang",
				"dodge","jindouyun",
				"force","wuxiangforce",
				"spells","dao",
				"stick","qianjun-bang",
			}),
		"weapon": W_DIR("stick"),
		]),

	"东海龙宫"	: ([
		"class"	: "xian",
		"skills": ({	"unarmed","dragonfight",
				"parry","fengbo-cha",
				"dodge","dragonstep",
				"force","dragonforce",
				"spells","seashentong",
				"fork","fengbo-cha",
			}),
		"weapon": W_DIR("fork"),
		]),

	"月宫"		: ([
		"class"	: "xian",
		"skills": ({	"unarmed","baihua-zhang",
				"parry","snowsword",
				"dodge","moondance",
				"force","moonforce",
				"spells","moonshentong",
				"sword","snowsword",
			}),
		"weapon": W_DIR("sword"),
		]),

	"阎罗地府"	: ([
		"class"	: "xian",
                  "skills": ({    "unarmed","jinghun-zhang",
				"parry","kusang-bang",
				"dodge","ghost-steps",
				"force","tonsillit",
				"spells","gouhunshu",
				"stick","kusang-bang",
			}),
		"weapon": W_DIR("stick"),
		]),

        "昆仑山玉虚洞"	: ([
        	"class"	: "xian",
        	"skills": ({	"unarmed","kaitian-zhang",
        			"parry","dashen-bian",
        			"dodge","lingyunbu",
        			"force","xuanzong-force",
        			"spells","yuxu-spells",
        			"whip","dashen-bian",
        		}),
        	"weapon": W_DIR("whip"),
        	]),

        "三界散仙"	: ([
        	"class" : "xian",
        	"skills": ({	"unarmed","ice_fire_zhang",
        			"parry","spysword",
        			"dodge","binfen-steps",
        			"force","butian-force",
        			"spells","mysticism",
        			"sword","spysword",
        		}),
        	"weapon": W_DIR("sword"),
        	]),

	"武圣门"	: ([
		"class"	: "xian",
        	"skills": ({	"unarmed","fumobashi",
        			"parry","wuying",
        			"dodge","mizongbu",
        			"force","xiantian",
        			"spells","feisheng",
        			"sword","wuying",
        		}),
        	"weapon": W_DIR("sword"),
        	]),
/*********************************************/
	"少林寺"	: ([
		"class"	: "human",
        	"skills": ({	"unarmed","jingang-leg",
                                "parry","zui-gun",
        			"dodge","shaolin-shenfa",
        			"force","yijinjing",
        			"spells","chanzong",
        			"stick","zui-gun",
        		}),
        	"weapon": W_DIR("stick"),
        	]),

	"神剑山庄"	: ([
		"class"	: "human",
        	"skills": ({	"unarmed","lianhuan-zhang",
        			"parry","duo-sword",
        			"dodge","shadowsteps",
        			"force","cloudforce",
        			"spells","xueying-xianfa",
        			"sword","duo-sword",
        		}),
        	"weapon": W_DIR("sword"),
        	]),

	"蜀山剑派"	: ([
		"class"	: "human",
        	"skills": ({	"unarmed","hunyuan-zhang",
        			"parry","yujianshu",
        			"dodge","sevensteps",
        			"force","zixia-shengong",
        			"spells","taoism",
        			"sword","yujianshu",
        		}),
        	"weapon": W_DIR("sword"),
        	]),

	"峨嵋派"	: ([
		"class"	: "human",
        	"skills": ({	"unarmed","jinding-zhang",
        			"parry","tianlei-sword",
        			"dodge","zhutian-bu",
        			"force","emeiforce",
        			"spells","mahayana",
        			"sword","tianlei-sword",
        		}),
        	"weapon": W_DIR("sword"),
        	]),

	"剑客联盟"	: ([
		"class"	: "human",
        	"skills": ({	"unarmed","kongshoudao",
        			"parry","feitian-sword",
        			"dodge","fengyu-piaoxiang",
        			"force","guixi-force",
        			"spells","renshu",
        			"sword","feitian-sword",
        		}),
        	"weapon": W_DIR("sword"),
        	]),

	"江湖浪子"	: ([
		"class"	: "human",
        	"skills": ({	"unarmed","lingxiyizhi",
        			"parry","mozi-sword",
        			"dodge","piaoxiang",
        			"force","wuji-force",
        			"spells","tianjijue",
        			"sword","mozi-sword",
        		}),
        	"weapon": W_DIR("sword"),
        	]),

	"将军府"	: ([
		"class"	: "human",
        	"skills": ({	"unarmed","changquan",
        			"parry","sanban-axe",
        			"dodge","yanxing-steps",
        			"force","lengquan-force",
        			"spells","baguazhou",
        			"axe","sanban-axe",
        		}),
        	"weapon": W_DIR("axe"),
        	]),

	"明教"		: ([
		"class"	: "human",
        	"skills": ({	"unarmed","qishang-quan",
        			"parry","shenghuo-ling",
        			"dodge","qingfu-shenfa",
        			"force","jiuyang-shengong",
        			"spells","qiankun-danuoyi",
        			"sword","shenghuo-ling",
        		}),
        	"weapon": W_DIR("sword"),
        	]),
/*****************************************/
	"陷空山无底洞"		: ([
		"class"	: "yao",
        	"skills": ({	"unarmed","yinfeng-zhua",
        			"parry","kugu-blade",
        			"dodge","lingfu-steps",
        			"force","huntian-qigong",
        			"spells","yaofa",
        			"blade","kugu-blade",
        		}),
        	"weapon": W_DIR("blade"),
        	]),

	"火云洞"		: ([
		"class"	: "yao",
        	"skills": ({	"unarmed","moyun-shou",
        			"parry","wuyue-spear",
        			"dodge","moshenbu",
        			"force","huomoforce",
        			"spells","pingtian-dafa",
        			"spear","wuyue-spear",
        		}),
        	"weapon": W_DIR("spear"),
        	]),

	"大雪山"		: ([
		"class"	: "yao",
        	"skills": ({	"unarmed","cuixin-zhang",
        			"parry","bainiao-jian",
        			"dodge","xiaoyaoyou",
        			"force","ningxie-force",
        			"spells","dengxian-dafa",
        			"sword","bainiao-jian",
        		}),
        	"weapon": W_DIR("sword"),
        	]),

	"轩辕古墓"		: ([
		"class"	: "yao",
        	"skills": ({	"unarmed","jiuyin-zhua",
        			"parry","qinghu-jian",
        			"dodge","kongming-steps",
        			"force","jiuyin-force",
        			"spells","youming-spells",
        			"sword","qinghu-jian",
        		}),
        	"weapon": W_DIR("sword"),
        	]),

	"盘丝洞"		: ([
		"class"	: "yao",
        	"skills": ({	"unarmed","lanhua-shou",
        			"parry","yinsuo-jinling",
        			"dodge","yueying-wubu",
        			"force","jiuyin-xinjing",
        			"spells","pansi-dafa",
        			"whip","yinsuo-jinling",
        		}),
        	"weapon": W_DIR("whip"),
        	]),

	"三界山"		: ([
		"class"	: "yao",
        	"skills": ({	"unarmed","lanhua-shou",
        			"parry","huxiaojian",
        			"dodge","zhaoyangbu",
        			"force","huntianforce",
        			"spells","tianmogong",
        			"sword","huxiaojian",
        		}),
        	"weapon": W_DIR("whip"),
        	]),

	"魔界"		: ([
		"class"	: "yao",
        	"skills": ({	"unarmed","shifo-zhi",
        			"parry","xueling-jian",
        			"dodge","moshenbu",
        			"force","heilian-force",
        			"spells","molian-spells",
        			"sword","xueling-jian",
        		}),
        	"weapon": W_DIR("sword"),
        	]),
]);