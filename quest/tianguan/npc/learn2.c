inherit NPC;

void check_player();

mapping fam = ([
        "南海普陀山" : ([
                "skill"  : ([
                        "force"   : ({"lotusforce",}),
                        "spells"  : ({"buddhism",}),
                        "dodge"   : ({"lotusmove",}),
                        "parry"   : ({"lunhui-zhang"}),
                        "staff"   : ({"lunhui-zhang"}),
                        "spear"   : ({"huoyun-qiang"}),
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
                        "parry"   : ({"wusi-mace"}),
                        "mace"    : ({"jinglei-mace"}),
                        "unarmed" : ({"changquan",}),
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
        
void setname(string family)
{
string tmp,*skills,*ss;
int i,k;        
mapping tt,name = NAME_D->random_name("female");    

tt = query_skills();
if ( tt && mapp(tt) )
        {
        skills = keys(tt);
        for(i=0;i<sizeof(skills);i++)
                delete_skill(skills[i]);
        }       
set_name(name["name"],name["id"]);
set("gender", ({"女性","男性"})[random(2)]);
set("age", 26+random(60));

tt = fam[family];
if ( tt["title"] )
        tmp = tt["title"];
else    tmp = "授业师傅";
set("门派",family);
set("title",family+" 授业师傅");
if ( tt["class"] )
        set("class",tt["class"]);
if ( tt["national"] )
        set("national",tt["national"]);
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
        set_skill(tmp,1500);
        ss = tt[tmp];
        k = random(sizeof(ss));
        if ( ss[k] )
                {
                set_skill(ss[k],1500);
                map_skill(tmp,ss[k]);
                }
        }
setup(); 
}

void create()
{
string family,*fams;
fams = keys(fam);
family = fams[random(sizeof(fams))];
setname(family);
}

int recognize_apprentice(object me)
{
return 1;
}
        
int prevent_learn(object me,string skill)
{
string family;  
object npc,*inv;
int i;  
if ( !me || !skill )
        return 1;
if ( !me->query("新任务/门派挑战/千面怪")
  || me->query("新任务/门派挑战/num")<9 )
        {
        command("say 你哪有这个资格！");
        return 1;
        }
if ( !is_chinese(to_chinese(skill)) )
        return 1;       
if ( family=me->query("family/family_name") )
        {
        if ( family!=query("门派") )
                {
                inv = all_inventory(environment());
                for(i=0;i<sizeof(inv);i++)
                        {
                        if ( !inv[i] 
                          || userp(inv[i]) 
                          || inv[i]->query("门派")!=family )
                                continue;
                        say(name()+"说道：这位"+RANK_D->query_respect(me)+"，你还是去向"+inv[i]->name()+"道友学习吧。\n");
                        return 1;
                        }
                command("say 我可不配做你的师傅。");
                npc = new(__DIR__"learn");
                npc->setname(family);
                if ( npc && npc->move(environment()) )
                        {
                        message_vision(npc->name()+"从上面走了下来。\n",me);
                        command("ah");
                        say(name()+"说道：这位"+RANK_D->query_respect(me)+"，你还是去向"+npc->name()+"道友学习吧。\n");
                        }
                return 1;
                }
        }
else    {
         if ( skill!="literate" )
                     {
                     command("say 没门派的只能学读书识字了。");
                     return 1;
                     }
        }
if ( !me->query_skill(skill,1) )
        {
        say(name()+"说道：这位"+RANK_D->query_respect(me)+"，"+to_chinese(skill)+"我没有细研究过，没法教你。\n",me);
        return 1;
        }
if ( me->query_temp("kailai_no_learn") )
      {
      write("开来已人满为患，"+name()+"不想再教你功夫。\n");
      return 1;
      }
return 0;
}

void remove_player(object who)
{
remove_call_out("remove_player");       
if ( !who || !present(who,environment()) )
        return;
if ( wizardp(who) )  tell_object(who,name()+"朝你点了点头。\n");
who->delete_temp("kailai_no_learn");    
MISC_D->random_capture(who,1,1); 
}       

int heal_up()
{
object *inv;
int i;
inv = all_inventory(environment());
for(i=0;i<sizeof(inv);i++)
        {
        if ( !userp(inv[i]) )
                continue;
        if ( inv[i]->query_temp("kailai_no_learn") )
                {
                inv[i]->start_busy(3);
                remove_call_out("remove_player");
                call_out("remove_player",1+random(3),inv[i]);
                }
        else    {
                if ( !inv[i]->query_temp("kailai_learn") )
                        inv[i]->set_temp("kailai_learn",time());
                if ( time()>inv[i]->query_temp("kailai_learn")+43200 )
                        {
                        inv[i]->start_busy(3);
                        remove_call_out("remove_player");
                        call_out("remove_player",1+random(3),inv[i]);
                        }
                }
        }
return ::heal_up()+1;
}                        
