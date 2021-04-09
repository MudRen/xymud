#include <ansi.h> 
#include <combat.h> 
inherit SUPER_NPC;

void create()
{
        set_name("白僵尸",({"jiang shi","shi","jiangshi","zambie"}));
        set("gender","男性");
        set("age",17+random(20));
        create_family("陷空山无底洞",4, "弟子");
        setup();
}

int information(object who)
{
        int i;
        if( !who || query("create") )
                return 0;
        i = who->query_level(); 
        if( i<15)
                i = 15;
        if( i>39 )
                i = 39;         
        if( i<10 )
                set("title","普通");
        else    set("title",chinese_number((i)/10*10)+"年");    
        set_level(i);
        set("per",1);
        set("attitude", "aggressive");
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
        map_skill("sword", "qixiu-jian");
        map_skill("unarmed", "yinfeng-zhua");
        map_skill("spells", "yaofa");
        map_skill("parry", "qixiu-jian");
        map_skill("dodge", "lingfu-steps");
        map_skill("blade", "kugu-blade");
        
        set("force_factor",1);
        set("mana_factor",10*i);
        
        set("water", 200000);
        set("food", 200000);

        set_temp("armor_level",i);
        set_temp("weapon_level",i);
        set("env/test","HIM");
        if( random(2) )
                set("guai_type","no_busy");
        else if( random(2) )
                set("guai_type","no_combat");
        else    set("guai_type","no_spells");
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
        carry_object(0,"blade",1)->wield();
        carry_object(0,"sword",1);
        carry_object(0,"unarmed",1);
        add_temp("apply/max_kee",400*i);
        add_temp("apply/max_sen",400*i);
        add_temp("apply/combat_def",500);
        add_temp("apply/spells_def",600);
        set("create",1);
        powerup(0,1);
        return 1;
}

string name()
{
        string str = ::name();
        if( !query("guai_type") )
                return str;
        set("title",HIR"精英"NOR);              
        switch(query("guai_type"))
        {
                case "no_busy"  : return str+"[轻灵]";
                case "no_combat": return str+"[厚土]";
                default : return str+"[驭法]";
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
        object ob,weapon;
        int i,succ;
        string str,file,*dir;

        message_vision (HIC"\n$N"HIC"「啪」的一声倒在地上，挣扎着抽动了几下就化成了一堆碎泥块。\n\n"NOR,this_object());
        if( !who || !userp(who) || !present(who,environment()) 
         || (!wizardp(who)&& who->query_level()>39)
         || !query("create") )
        {
                destruct(this_object());
                return;
        }
        
        succ = who->query_kar();
        if( random(succ)>28 )
        {
                file = sprintf("/d/maze/qingling-1/obj/sj%d1",random(2));
                ob = new(file);
                ob->set("owner_id",who->query("id"));
                if( !ob->move(who) )
                {
                        destruct(ob);
                        tell_object(who,HIR"【副本】始皇陵一层：你的背包满了。\n"NOR);
                }
                else    tell_object(who,HIY"【副本】始皇陵一层：你得到了 "HIG+obj_name(ob)+HIY" 。\n"NOR);
        }
        
        dir = ({
                "hand","neck","ring","shield","waist","wrists",
        });
        if( this_object()->query_level()<30 )
                i = 1;
        else    i = random(2)+random(2)+1;      
        while(i--)
        {
                file = dir[random(sizeof(dir))];
                if( file )
                {
                        dir-=({file});
                        ob = new("/d/obj/narmor/"+file);
                        ob->set("from","【始皇陵一层副本】");
                        if( this_object()->query_level()<30 )
                                set("env/test",({"HIB","HIC","HIC","HIC","HIC","HIC","HIR",})[random(7)]);
                        else if( random(succ)>25 )
                                set("env/test",({"HIB","HIC","HIR","HIM"})[random(4)]);
                        else    set("env/test",({"HIB","HIC"})[random(2)]);
                        ob->init_armor(this_object());
                        if( !ob->move(who) )
                        {
                                destruct(ob);
                                tell_object(who,HIR"【副本】始皇陵一层：你的背包满了。\n"NOR);
                        }
                        else    tell_object(who,HIY"【副本】始皇陵一层：你得到了 "HIG+obj_name(ob)+HIY" 。\n"NOR);
                }
        }
        
        if( objectp(weapon=who->query_temp("weapon")) )
                file = weapon->query("skill_type");
        else    file = "unarmed";       
        dir = ({
                "axe","blade","blade","hammer","mace","spear",
                "staff","stick","sword","unarmed","whip","fork",
        });
        if( member_array(file,dir)==-1 || random(2) )
                file = dir[random(sizeof(dir))];
        
        ob = new("/d/obj/nweapon/"+file);
        ob->set("from","【始皇陵一层副本】");
        if( this_object()->query_level()<30 )
                set("env/test",({"HIB","HIC","HIC","HIC","HIC","HIC","HIR",})[random(7)]);
        else if( random(succ)>25 )
                set("env/test",({"HIB","HIC","HIR","HIM"})[random(4)]);
        else    set("env/test",({"HIB","HIC"})[random(2)]);
        ob->init_weapon(this_object());
        if( !ob->move(who) )
        {
                destruct(ob);
                tell_object(who,HIR"【副本】始皇陵一层：你的背包满了。\n"NOR);
        }
        else    tell_object(who,HIY"【副本】始皇陵一层：你得到了 "HIG+obj_name(ob)+HIY" 。\n"NOR);

        if( random(succ)>18 )
        {
                file = sprintf("/d/maze/qingling-1/obj/gin%d",1+random(4));
                ob = new(file);
                ob->set("owner_id",who->query("id"));
                if( !ob->move(who) )
                {
                        destruct(ob);
                        tell_object(who,HIR"【副本】始皇陵一层：你的背包满了。\n"NOR);
                }
                else    tell_object(who,HIY"【副本】始皇陵一层：你得到了 "HIG+obj_name(ob)+HIY" 。\n"NOR);
        }
        
        if( random(this_object()->query_level())>3 )
        {
                ob = new("/d/maze/qingling-1/obj/bangding.c");
                if( !ob->move(who) )
                {
                        destruct(ob);
                        tell_object(who,HIR"【副本】始皇陵一层：你的背包满了。\n"NOR);
                }
                else    tell_object(who,HIY"【副本】始皇陵一层：你得到了一块"HIG"绑定用的灵石"HIY"。\n"NOR);
        }
                
        destruct(this_object());        
        return;
}

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

