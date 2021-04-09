// jia-shen.c 假身
#include <ansi.h>

inherit NPC;

void create()
{
	set_name("真身",({"zhen shen"}));
	set("gender","男性");
	set("age",30);
	set("str",30);
	set("per",20);
	set("combat_exp",1000);
	set("daoxing",1000);
        set("attitude", "friendly");
	set_skill("dodge",10);
	set_skill("moshenbu",10);
	map_skill("dodge","moshenbu");

	setup();
}

void copy_status(object me,object ob)
{
//	object *inv;
	mapping skill_status,map_status;
	string *sname,*mname;
	int i;
	me->set("id", ob->query("id")+"'s zhenshen");
	me->set("name",ob->query("name"));
	me->set("title",ob->query("title"));
	me->set("nickname",ob->query("nickname"));
	skill_status=me->query_skills();
	sname=keys(skill_status);
	for(i=0;i<sizeof(skill_status);i++) {
		me->delete_skill(sname[i]);
	}
	skill_status=ob->query_skills();
	sname=keys(skill_status);
	for(i=0;i<sizeof(skill_status);i++) {
		me->set_skill(sname[i],skill_status[sname[i]]);
	}
	if ( mapp(map_status = me->query_skill_map()) ) {
                mname  = keys(map_status);

                for(i=0; i<sizeof(map_status); i++) {
                        me->map_skill(mname[i]);
                }
        }

        map_status = ob->query_skill_map();
        mname  = keys(map_status);

        for(i=0; i<sizeof(map_status); i++) {
                me->map_skill(mname[i], map_status[mname[i]]);
        }
	me->set_level(ob->query_level());
	me->set("force_factor",ob->query("force_factor"));
	me->set("mana_factor",ob->query("mana_factor"));
	me->set("max_kee",ob->query_maxkee());
	me->set("max_sen",ob->query_maxsen());
	setup();
	powerup();
}

void die()
{
	string owner;
	object owner_ob;
	owner = query("owner");
	if( objectp(owner_ob = find_player(owner)) ) {
                        tell_object(owner_ob, "你的真身被人杀死了，你觉得一阵天旋地转....\n");
			owner_ob->move("/obj/void");
			owner_ob->unconcious(); 
	}
	if( environment() )
		message("vision",HIB + name() + "身子一晃，变成一股青烟散去了。\n" NOR,environment(),this_object() );
	destruct(this_object());
}

int heal_up()
{	object owner_ob;
	object me=this_object();
        if( objectp(owner_ob=query("owner_ob")) 
		&&  owner_ob->query_temp("in_hell") ) {
		::heal_up();
		return 1;
	}
        call_out("leave", 1);
        return ::heal_up();
}

void leave()
{
	if(this_object()) { //mon 11/23/97
      		if( environment() )
        		message("vision",HIB + name() + "身子一晃，变成一股青烟散去了。\n" NOR,environment(),this_object() );
        	destruct(this_object());
      	}
      	return;
}

void invocation(object who)
{	object me=this_object();
	copy_status(me,who);
	set("owner", who->query("id"));
	set("owner_ob", who);
}

int is_zhenshen() { return 1; }
