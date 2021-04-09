//挑战NPC设定
//Created By snowtu 2007
//last Edited by snowtu 2008
#include <ansi.h>
inherit NPC;

void setname(){return;}
void reward_ob(object who);
int is_job(){return 1;}       

int is_pass(object who)
{
        if( !who )
                return 0;
        return who->query("新任务/门派挑战/"+query("name"));
}

object carry_obj(string file)
{
        object ob,temp;
        if( file->query_unique() )  
        {
                if( clonep() ) 
                {  
                        if( !objectp(ob = new(file->clone_file())) ) 
                                return 0;
                } 
                else 
                {
                if( !file->query("replace_file") 
                 || !objectp(ob = new(file->query("replace_file"))) ) 
                        return 0;
                }
        }
        else if( !objectp(ob = new(file)) ) 
                return 0;
        ob->set("keep_this",1);
        ob->set("value",0);
        temp = new("obj/armor");
        if( temp )
        {
                ob->set_name(temp->name(1),temp->parse_command_id_list());
                destruct(temp);
        }       
        ob->move(this_object());
        return ob;
}

void setup()
{
        mapping my;
        int qi,shen,i;
        string myforce,myspells,*gifts;
        int myforce_lvl,myspells_lvl;
        object ob = this_object();

        my = query_entire_dbase();
        my["max_force"] = query_skill("force")/2*50;
        my["max_mana"] = query_skill("spells")/2*30;
        my["mana"] = my["max_mana"]*2;
        my["force"] = my["max_force"]*2;
        if( undefinedp(my["age"]) ) my["age"] = random(30) + 15;
        gifts = ({
                "str","cor","int","cps","per","con","kar"
        });
        for(i=0;i<sizeof(gifts);i++)
                if( undefinedp(my[gifts[i]]) ) 
                        my[gifts[i]] = random(21) + 10;
        qi= (my["con"]+my["str"])/2;
        shen= (my["spi"]+my["int"])/2;

        if( undefinedp(my["max_kee"]) ) 
        {
                if( my["age"]<=30 ) 
                        my["max_kee"] = (my["age"]-4)*qi;
                else    my["max_kee"] = 26*qi;
                myforce=ob->query_skill_mapped("force");
                myforce_lvl=ob->query_skill("force");
                my["max_kee"]+= myforce_lvl*3;
                if( my["max_force"]>0 ) 
                        my["max_kee"] += my["max_force"]*2/5;
                if( my["max_kee"]<1 ) 
                        my["max_kee"]=1;
        }
        if( undefinedp(my["max_sen"]) ) 
        {
                if( my["age"] <= 14 ) my["max_sen"] = 10*shen;
                else if( my["age"] <= 30 ) my["max_sen"] = (my["age"] - 4) *shen;
                else if( my["age"] <= 40 ) my["max_sen"] = 26 * shen;
                else    
                {
                        if( my["fake_age"] <= 40 )
                                my["max_sen"] = 26 * shen;
                        else    my["max_sen"] = 26 * shen - (my["fake_age"]- 40) * 5;
                }
                myspells=ob->query_skill_mapped("spells");
                myspells_lvl=ob->query_skill("spells");
                my["max_sen"]+=myspells_lvl*3;
                if( my["max_mana"]>0 ) 
                        my["max_sen"] += my["max_mana"]*2/5;
                if( my["max_sen"]<1 ) 
                        my["max_sen"]=1;
        }
        if( undefinedp(my["unit"])) my["unit"]="位";
        if( undefinedp(my["gender"])) my["gender"]="男性";
        if( undefinedp(my["can_speak"])) my["can_speak"]=1;
        if( undefinedp(my["attitude"])) my["attitude"]="peaceful";
        if( undefinedp(my["limbs"])) 
                my["limbs"]= ({
                        "头部", "颈部", "胸口", "后心", "左肩", "右肩", "左臂",
                        "右臂", "左手", "右手", "腰间", "小腹", "左腿", "右腿",
                        "左脚", "右脚"
                });
        set_heart_beat(1);
        enable_player();
        set_max_items(30);
        this_object()->update_age(); // mon 7/3/99
        if( !query("race") )
                set("race", "人类");
        if( !query_max_encumbrance() )
                set_max_encumbrance( my["str"]*5000 +query_skill("unarmed",1)*200);
        reset_action();
        set("force_factor",query_skill("force")/4);
        set("mana_factor",query_skill("spells")/4);
        set("food",1000);
        set("water",1000);
        powerup(1);     
        ::setup();
        reset_eval_cost();
        gifts = ({
                "/d/npc/obj/armor",
                "/d/npc/obj/windyshoes",
                "/d/npc/obj/necklace",
                "/d/npc/obj/ring",
                "/d/npc/obj/jrbs",
                "/d/npc/obj/pifeng",
                "/d/npc/obj/kui",
                "/d/obj/suburb/que",
        });
        for(i=0;i<sizeof(gifts);i++)
                carry_obj(gifts[i])->wear();
}

void create()
{
        set_name("门派精灵",({"menpai"}));      
        set("combat_exp", 70000000);
        set("env/brief_message",3);
        set("daoxing", 7000000);
        set("fangcun/panlong_accept","done");
        set("no_sleep",1);
        setname();
        setup();
        add_temp("apply/damage",150);
        add_temp("apply/armor",350);
}

int accept_fight(object who)
{
        return 0;
}

int prevent_learn(object me,string skill)
{
        command("say 我久不授徒，已尽数忘光了，你还是去 开来 找合适你的师傅吧。");
        return 1;
}

void reward_ob(object who)
{
        object gift;    
        mapping skill;
        string *skills,temp;
        int i,pp;
        
        if( !who )
                return;
        if( who->query("新任务/镖_pot")<10 )  
                tell_object(who,"你灵力不够，无法在此地图得到任何附加奖励。\n");
        if( query("id")!=environment()->query("master") )
        {
                pp = who->query("新任务/门派挑战/"+environment()->query("master")+"_dizi_killed");
                if( pp<1 )
                        pp = 1;
                if( random(pp)==0 )
                {               
                        if( who->query_temp("weapon") )
                        {
                                temp = who->query_temp("weapon")->query("skill_type");
                                if( !who->query_skill(temp,1) )
                                        temp = "unarmed";
                        }
                        else    temp = "unarmed";
                        if( !who->query_skill(temp,1) )
                                return;
                        temp = who->query_skill_mapped(temp);
                        if( !temp || !stringp(temp) || !who->query_skill(temp,1) )
                                return;
                        if( who->query("新任务/镖_pot")>=10 )
                        {
                                who->improve_skill(temp,random(300)+1,0);       
                                tell_object(who,"你杀死了"+query("name")+",你的"+to_chinese(temp)+"熟练度增加了。\n");
                                who->add("新任务/镖_pot",-1);
                                who->save();
                                tell_object(who,"因为获得追加奖励，你的灵力减少了一点。\n");
                        }
                }
                pp = who->query_temp("tiaozhan_weapon_get");
                if( pp<5 )
                        pp = 5;
                if( wizardp(who) )
                        pp = 2; 
                if( random(pp)==0 && who->query("新任务/镖_pot")>=10 )
                {
                        gift = new("/obj/weapon");
                        if( gift && gift->move(who) )
                        {
                                CHANNEL_D->do_channel(environment(),"chat",who->name(1)+"于"+environment()->query("short")+"打败"+name()+"，得到了"+gift->name()+HIC"。"NOR);
                                who->add("新任务/镖_pot",-3);
                                who->save();
                                tell_object(who,"因为获得追加奖励，你的灵力减少了三点。\n"); 
                                who->add_temp("tiaozhan_weapon_get",1);
                        }
                }
        }
        else if( this_object()->is_boss() )
        {
                if( !is_pass(who) )
                {
                        who->set("新任务/门派挑战/"+query("name"),1);
                        who->add("新任务/门派挑战/num",1);
                }
                pp = who->query("新任务/门派挑战/"+environment()->query("master")+"_master_killed");
                if( pp<1 )
                        pp = 1;
                if( random(pp)==0 )
                {       
                        skill = who->query_skills();
                        skills = keys(skill);
                        i = sizeof(skills);
                        i = random(i);
                        temp = skills[i];
                        if( !temp || !stringp(temp) || !who->query_skill(temp,1) )
                                return;
                        if( who->query("新任务/镖_pot")>=10 )
                        {                        
                                tell_object(who,"你杀死了"+query("name")+",你的"+to_chinese(temp)+"熟练度增加了。\n");
                                if( random(5)==0 )
                                        who->improve_skill(temp,10000000,0);
                                else    who->improve_skill(temp,500+random(1500),1);    
                                if( random(2) )
                                {
                                        who->add("combat_exp",8000+random(1000)*2);
                                        tell_object(who,"你的武学经验增加了。\n");
                                }
                                if( random(3) )
                                {
                                        who->add("daoxing",10000+random(5000)*2);
                                        tell_object(who,"你的道行修为增加了。\n");
                                }
                                if( random(10)==1 )
                                {
                                        who->add("maximum_force",50);
                                        who->add("max_force",50);
                                        tell_object(who,"你的内力修为增加了。\n");
                                }
                                if( random(8)==0 && who->query("obstacle/reward") )
                                {
                                        who->add("obstacle/rebirth",-1); 
                                        tell_object(who,"佛祖奖励你一根救命毫毛。\n");  
                                }
                                who->add("新任务/镖_pot",-5);
                                who->save();
                                tell_object(who,"因为获得追加奖励，你的灵力减少了五点。\n"); 
                        }
                }
                pp = who->query_temp("tiaozhan_armor_get");
                if( pp<5 )
                        pp = 5;
                if( wizardp(who) )
                        pp = 2; 
                if( random(pp)==0 && who->query("新任务/镖_pot")>=10 )
                {
                        gift = new("/obj/armor");
                        if( gift && gift->move(who) )
                        {
                                CHANNEL_D->do_channel(environment(),"chat",who->name(1)+"于"+environment()->query("short")+"打败"+name()+"，得到了"+gift->name()+HIC"。"NOR);                           
                                who->add_temp("tiaozhan_armor_get",1);
                                who->add("新任务/镖_pot",-5);
                                who->save();
                                tell_object(who,"因为获得追加奖励，你的灵力减少了五点。\n");                         
                        }
                }
        }
        return;
}

void heart_beat()
{
        int ss; 
        object weapon,me = this_object();
        if( !environment() )
                return;
        if( query("force")<500 )
        {
                if( query("kee")<=0 || query("eff_kee")<=0 )
                {
                        die();
                        return;
                }
                if( query("sen")<0 || query("eff_sen")<=0 )
                {
                        unconcious();
                        return;
                }
        }
        if( me->is_fighting() )
        {
                int i;
                object *enemy = query_enemy();  
                for(i=0;i<sizeof(enemy);i++)
                {
                        if( !enemy[i] || !present(enemy[i],environment()) )
                        {
                                me->clean_up_enemy();   
                                me->clear_condition();
                                powerup(random(2));
                                if( enemy[i] )
                                {
                                        me->remove_killer(enemy[i]);
                                        enemy[i]->remove_killer(me);    
                                }
                        }
                }       
        }
        if( query("eff_kee") < query("max_kee") )
                QUEST_D->addEffKee(me);
        if( query("kee") < query("eff_kee") )
                QUEST_D->addKee(me);
        if( query("sen") < query("eff_sen") )
                QUEST_D->addSen(me);
        if( query("eff_sen") < query("max_sen") )
                QUEST_D->addEffSen(me);
        if( me->is_boss() )
                ss = 5;
        else    ss = 25;
        if( me->is_busy() &&  random(ss)==0 )
        {
                me->start_busy(1,10000);
                me->interrupt_me(me,"不动"); 
                me->reset_action(); 
        } 
        me->clear_condition();
        if( me->is_fighting() )
        {
                this_object()->clean_up_enemy();
                this_object()->add("force",5+random(5));
                ss*= 3;
                switch(random(ss))
                {
                        case 0 :
                        case 1 :
                        case 5 : QUEST_D->randomExert(me);break;
                        case 2 :
                        case 3 :
                        case 8 :
                        case 7 :
                        case 9: QUEST_D->randomPfm(me);break;                
                }
        }
        ::heart_beat();
}

varargs int receive_damage(string type, int damage, object who)
{
        if( !who ) damage = 0;
        if( who && !userp(who) )   
        {
                damage = 0;
                this_object()->remove_killer(who);
                who->remove_killer(this_object());
        }
        return ::receive_damage(type,damage,who);
}

varargs int receive_wound(string type, int damage, object who)
{
        if( !who ) damage = 0;
        if( who && !userp(who) )   
        {
                damage = 0;
                this_object()->remove_killer(who);
                who->remove_killer(this_object());
        }
        return ::receive_wound(type,damage,who);
}

void help_kill(object who)
{
        int i;
        object *inv,npc;
        if( !who )      return;
        inv = all_inventory(environment());
        for(i=0;i<2;i++)
        {
                npc = inv[random(sizeof(inv))]; 
                if( npc && living(npc) && !userp(npc) //玩家或昏迷的
                 && !npc->is_fighting(who)                     //在战斗的
                 && npc!=this_object()                          //..
                 && npc->is_job() )                  //非挑战NPC
                {
                        say( sprintf("%s在旁说道：%s道友，休要惊慌，我来助你一臂之力。\n",npc->name(),this_object()->name(1)[0..1]));
                        npc->kill_ob(who);
                }
        }
        return;       
}
        
void kill_ob(object who)
{
        if( !who || !present(who,environment()) )  
        {        
                powerup();
                return;
        }
        help_kill(who);               
        ::kill_ob(who);
}
