#include <ansi.h> 
#include <combat.h> 
inherit SUPER_NPC;
 
void create()
{
        int i;
        mapping name = NAME_D->random_name2(0, 0, 0, 0, 0);
        set_name(name["name"],name["id"]);
        set("gender","男性");
        set("title",HIR"尸王"NOR);
        set("age",(17+random(20))*10);
        set("per",1);
        set("attitude", "aggressive");
        set("bellicosity",800);
        i = 39;
        set_level(i);
        set_skill("unarmed",i*10);
        set_skill("dodge",i*10);
        set_skill("parry",i*10);
        set_skill("stealing",i*10);
        set_skill("spells",i*10);
        set_skill("yinfeng-zhua",i*10);
        set_skill("lingfu-steps",i*10);
        set_skill("force",i*10);
        set_skill("sword",i*10);
        set_skill("qixiu-jian",i*10);
        set_skill("kugu-blade",i*10);
        set_skill("blade",i*10);
        set_skill("yaofa",i*10);
        set_skill("huntian-qigong",i*10);
        map_skill("force", "huntian-qigong");
        map_skill("unarmed", "yinfeng-zhua");
        map_skill("spells", "yaofa");
        map_skill("dodge", "lingfu-steps");
        map_skill("blade", "kugu-blade");
        map_skill("sword", "qixiu-jian");
        map_skill("parry", "qixiu-jian");
        
        set("force_factor",1);

        set("water", 200000);
        set("food", 200000);

        if( random(2) )
                set("guai_type","no_busy");
        else if( random(2) )
                set("guai_type","no_combat");
        else    set("guai_type","no_spells");
        
        set_temp("armor_level",i);
        set_temp("weapon_level",i);
        set("env/test","HIM");
        setup();
        carry_object(0,"cloth",1)->wear();
        carry_object(0,"armor",1)->wear();
        carry_object(0,"kui",1)->wear();
        carry_object(0,"pifeng",1)->wear();
        carry_object(0,"hands",1)->wear();
        carry_object(0,"neck",1)->wear();
        carry_object(0,"ring",1)->wear();
        carry_object(0,"wrists",1)->wear();
        carry_object(0,"shoes",1)->wear();
        carry_object(0,"waist",1)->wear();
        if( random(2) )
        {
                carry_object(0,"blade",1)->wield();
                map_skill("parry", "kugu-blade");
        }
        else    carry_object(0,"sword",1)->wield();
        add_temp("apply/max_kee",800*i);
        add_temp("apply/max_sen",800*i);
        add_temp("apply/combat_def",300);
        add_temp("apply/spells_def",300);
        powerup(0,1);
}

string short()
{
        string str = ::short();
        if( !query("guai_type") )
                return str;
        switch(query("guai_type"))
        {
                case "no_busy"  : return str+"["HIY"轻灵"NOR"]";
                case "no_combat": return str+"["HIC"厚土"NOR"]";
                default : return str+"["HIC"驭法"NOR"]";
        }
}

string obj_name(object ob)
{
        string str;
        if( !ob )
                return "";
        str = ob->name(1);
        str = COLOR_D->clean_color(str);
        return str;
}

void reward_ob(object who)
{
        object ob,xin,weapon;
        int i,succ;
        string file,*dir,arg;

        if( !who || !userp(who) || !present(who,environment()) 
         || (!wizardp(who)&& who->query_level()>39)
         || !query("create") )
        {
                message_vision (HIR"\n$N「啪」的一声倒在地上，挣扎着抽动了几下就死了。\n\n"NOR,this_object());          
                destruct(this_object());
                return;
        }
        message_vision (HIC"\n$N"HIC"「啪」的一声倒在地上，挣扎着抽动了几下就化成了一堆碎泥块。\n\n"NOR,this_object());
        
        arg = "";
        succ = who->query_kar();

        set_temp("weapon_level",25+random(15));
        set_temp("armor_level",25+random(15));

        dir = ({
                "hand","neck","ring","shield","waist","wrists",
                "armor","cloth","kui","pifeng","shoes",
        });
        i = random(3)+1;
        while(i--)
        {
                file = dir[random(sizeof(dir))];
                if( file )
                {
                        dir-=({file});
                        ob = new("/d/obj/narmor/"+file);
                        ob->set("from","【始皇陵一层副本】");
                        if( random(succ)>15 )
                                set("env/test",({"HIR","HIM",})[random(2)]);
                        else    set("env/test",({"HIR","HIB","HIB","HIB","HIB","HIR"})[random(6)]);     
                        ob->init_armor(this_object());
                        if( !ob->move(who) )
                        {
                                destruct(ob);
                                tell_object(who,HIR"【副本】始皇陵一层：你的背包满了。\n"NOR);
                        }
                        else    
                        {
                                tell_object(who,HIY"【副本】始皇陵一层：你得到了 "HIG+obj_name(ob)+HIY" 。\n"NOR);
                                arg+= obj_name(ob);
                                if( i!=0 )
                                        arg+= "、";
                        }
                }
        }
        
        if( objectp(weapon=who->query_temp("weapon")) )
                file = weapon->query("skill_type");
        else    file = "unarmed";       
        dir = ({
                "axe","blade","blade","hammer","mace","spear",
                "staff","stick","sword","unarmed","whip","fork",
        });
        if( member_array(file,dir)==-1 )
                file = dir[random(sizeof(dir))];
        
        ob = new("/d/obj/nweapon/"+file);
        ob->set("from","【始皇陵一层副本】");
        if( random(succ)>15 )
                set("env/test",({"HIR","HIM",})[random(2)]);
        else    set("env/test",({"HIR","HIB","HIB","HIB","HIB","HIR"})[random(6)]);     
        ob->init_weapon(this_object());
        if( !ob->move(who) )
        {
                destruct(ob);
                tell_object(who,HIR"【副本】始皇陵一层：你的背包满了。\n"NOR);
        }
        else    
        {
                tell_object(who,HIY"【副本】始皇陵一层：你得到了 "HIG+obj_name(ob)+HIY" 。\n"NOR);
                arg+= "、"+obj_name(ob);
        }
        
        if( random(succ)>8 )
        {
                file = sprintf("/d/maze/qingling-1/obj/gin%d",3+random(3));
                ob = new(file);
                ob->set("owner_id",who->query("id"));
                if( !ob->move(who) )
                {
                        destruct(ob);
                        tell_object(who,HIR"【副本】始皇陵一层：你的背包满了。\n"NOR);
                }
                else    
                {
                        tell_object(who,HIY"【副本】始皇陵一层：你得到了 "HIG+obj_name(ob)+HIY" 。\n"NOR);
                        arg+= "、"+obj_name(ob);
                }
        }
        if( random(succ)>10 )
        {
                file = sprintf("/d/maze/qingling-1/obj/sj%d%d",random(2),1+random(3));
                ob = new(file);
                ob->set("owner_id",who->query("id"));
                if( !ob->move(who) )
                {
                        destruct(ob);
                        tell_object(who,HIR"【副本】始皇陵一层：你的背包满了。\n"NOR);
                }
                else    
                {
                        tell_object(who,HIY"【副本】始皇陵一层：你得到了 "HIG+obj_name(ob)+HIY" 。\n"NOR);
                        arg+= "、"+obj_name(ob);
                }
        }        
        if( random(succ)>15 )
        {
                file = sprintf("/d/maze/qingling-1/obj/change%d",1+random(3));
                ob = new(file);
                ob->set("owner_id",who->query("id"));
                if( !ob->move(who) )
                {
                        destruct(ob);
                        tell_object(who,HIR"【副本】始皇陵一层：你的背包满了。\n"NOR);
                }
                else    
                {
                        tell_object(who,HIY"【副本】始皇陵一层：你得到了 "HIG+obj_name(ob)+HIY" 。\n"NOR);
                        arg+= "、"+obj_name(ob);
                }
        }
        if( random(succ)>5 )
        {
                file = ("/d/maze/qingling-1/obj/xiu");
                ob = new(file);
                ob->set("owner_id",who->query("id"));
                if( !ob->move(who) )
                {
                        destruct(ob);
                        tell_object(who,HIR"【副本】始皇陵一层：你的背包满了。\n"NOR);
                }
                else    
                {
                        tell_object(who,HIY"【副本】始皇陵一层：你得到了 "HIG+obj_name(ob)+HIY" 。\n"NOR);
                        arg+= "、"+obj_name(ob);
                }
        }
        i = random(3)+1;
        arg+= "、"+chinese_number(i)+"块绑定石";
        while(i--)
        {
                ob = new("/d/maze/qingling-1/obj/bangding.c");
                if( !ob->move(who) )
                {
                        destruct(ob);
                        tell_object(who,HIR"【副本】始皇陵一层：你的背包满了。\n"NOR);
                }
                else    tell_object(who,HIY"【副本】始皇陵一层：你得到了一块"HIG"绑定用的灵石"HIY"。\n"NOR);
        }
        CHANNEL_D->do_channel(this_object(),"rumor","听说"+who->name()+HIM"杀死了"HIY"尸王"HIM"，得到了"+arg+"。"NOR);
        who->set("maze/last_QLboss1",time());
        destruct(this_object());
}

int is_boss(){return 1;}

int accept_fight(object who)
{
        tell_object(who,HIC"僵尸呆呆的看着你。\n"NOR);
        return 0;
}

void kill_ob(object who)
{
        if( !this_object()->is_fihgting() )
        {
                powerup(0,1);
                stop_busy(100);
        }
        ::kill_ob(who);
}

varargs int receive_wound(string type, int damage, object who,mixed attack_type)
{
        if( who && who!=this_object() )
        {
                if( query("guai_type")=="no_busy" 
                 && this_object()->is_busy() )
                        damage = 0;
                else if( query("guai_type")=="no_combat"
                 && attack_type!=TYPE_CAST )
                        damage = 0;
                 else if( query("guai_type")=="no_spells"
                 && attack_type==TYPE_CAST )            
                        damage = 0;
        }               
        return ::receive_wound(type,damage,who,attack_type);
}

varargs int receive_damage(string type, int damage, object who,mixed attack_type)
{
        if( who && who!=this_object() )
        {
                if( query("guai_type")=="no_busy" 
                 && this_object()->is_busy() )
                        damage = 0;
                else if( query("guai_type")=="no_combat"
                 && attack_type!=TYPE_CAST )
                        damage = 0;
                 else if( query("guai_type")=="no_spells"
                 && attack_type==TYPE_CAST )            
                        damage = 0;
        }               
        return ::receive_damage(type,damage,who,attack_type);
}
