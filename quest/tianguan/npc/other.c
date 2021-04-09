inherit __DIR__"n.c";

mapping fam = ([
        "蜀山派" : ([
                "weapon" : ({"sword","whip",}),
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

        "大雪山" : ([
                "weapon" : ({"sword","blade",}),
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
                "title"   : "炼气士",
                "class"   : "swordsman",
                "national": "兽族",
                ]),
                        
        "三界散仙" : ([
                "weapon" : ({"sword"}),
                "skill"  : ([
                        "force"   : ({"butian-force",}),
                        "spells"  : ({"mysticism",}),
                        "dodge"   : ({"binfen-steps",}),
                        "parry"   : ({"spysword"}),
                        "sword"   : ({"spysword"}),
                        "unarmed" : ({"ice_fire_zhang",}),
                        "literate": ({0,}),
                        ]),
                "title"   : "炼气士",
                ]),
        "陷空山无底洞" : ([
                "weapon" : ({"sword","blade",}),
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
                "title"   : "炼气士",
                "national": "兽族",
                ]),
        "五庄观" : ([
                "weapon" : ({"sword"}),
                "skill"  : ([
                        "force"   : ({"zhenyuan-force",}),
                        "spells"  : ({"taiyi",}),
                        "dodge"   : ({"baguazhen",}),
                        "parry"   : ({"sanqing-jian"}),
                        "sword"   : ({"sanqing-jian"}),
                        "unarmed" : ({"wuxing-quan",}),
                        "literate": ({0,}),
                        ]),
                "title"   : "炼气士",
                ]),
]);
        
int is_boss(){return 1;}

void setname()
{
string family,tmp,*fams,*skills,*ss;
mixed *tmps;
int i,k;        
mapping tt,name = NAME_D->random_name("female");    
set_name("千面怪",({"qianmian guai","guai"}));
set("gender", ({"女性","男性"})[random(2)]);
set("age", 26+random(60));

fams = keys(fam);
family = fams[random(sizeof(fams))];

tmps = fam[family]["weapon"];
tmp = tmps[random(sizeof(tmps))];
set("weapon",tmp);

tt = fam[family];
if ( tt["title"] )
        tmp = tt["title"];
else    tmp = "弟子";
create_family(family,1,tmp);
add("title","(幻)");

if ( tt["class"] )
        set("class",tt["class"]);
if ( tt["national"] )
        set("national",tt["national"]);
        
set("chushi/chushi_shushan","yes");
set("chushi/chushi_xueshan","yes");
set("chushi/chushi_wdd","yes");
set("per", random(60));
set("int", 100);
set("con", 100);
set("str", 100);

tt = fam[family]["skill"];
skills = keys(tt);
i = sizeof(skills);
while(i--)
        {
        tmp = skills[i];
        if ( !tmp || !stringp(tmp) )
                continue;
        set_skill(tmp,900);
        ss = tt[tmp];
        k = random(sizeof(ss));
        if ( ss[k] )
                {
                set_skill(ss[k],900);
                map_skill(tmp,ss[k]);
                }
        }
}

void setup()
{
::setup();  
carry_object("/d/npc/obj/"+query("weapon"))->wield();
set("combat_exp",150000000);
set("daoxing",30000000);
}
