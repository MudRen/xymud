// bian.c
// by mon. 1/3/97

#include <ansi.h>

int do_bian(object me);

int main(object me, string arg)
{
	string id;
      	object who,obj;
      	int mana,spells,dmana;

      	seteuid(getuid());
	if( me->query_level()<40 )
		return notify_fail("你尚未筑基，变化不了。\n");
	if( me->is_fighting() )
        	return notify_fail("你正在战斗，无暇变身。\n");
	if( environment(me)->query("no_magic")
	 || environment(me)->query("no_bian") )
	 	return notify_fail("此处不允许变化。\n");
	if( me->query_temp("no_bian") )
		return notify_fail("你现在不能变身。\n");
      	if( me->is_busy() || me->query_temp("pending/exercising"))
		return notify_fail("你正忙着呢，没工夫变身。\n");

        if( !arg || arg=="me" || arg==me->query("id")) 
		who=me;
      	else 
      	{
		if(!objectp(who=present(arg,environment(me)))) 
	   		return notify_fail("你想变成谁？\n");
      	}
	if( arg=="coin" || arg=="gold" || arg=="silver" || arg=="cash" ) 
		return notify_fail("想做假钞？\n");

	if(who==me) 
	{
		me->delete_temp("spellslevel");
		me->delete_temp("apply/name");
		me->delete_temp("apply/id");
		me->delete_temp("apply/short");
		me->delete_temp("apply/long");
		me->delete_temp("family");
		me->delete_temp("no_heal_up/bian");
		if(me->query_temp("d_mana")) 
		{
	  		me->delete_temp("d_mana");
	  		while( environment(me)->is_character() )
	     			me->move(environment(environment(me)));
			message_vision(HIY "$N"HIY"口念咒语，身形一晃，现了真身。\n"NOR,me);
        	} 
        	else	return notify_fail("你想变成谁？\n");
	}
	else 
	{
		if( who->query_temp("no_bian") )
			return notify_fail(who->name()+"朝你摇了摇头。\n");
        	spells = me->query_skill("spells");
		mana=me->query("mana");
		if( spells<25 )
	   		return notify_fail("你的法术不够。\n");
		if( mana<150)
			return notify_fail("你目前法力不够充盈。\n");
		if( wizardp(who) && !wizardp(me))
	   		return notify_fail("你的法术不足以变成巫师。\n");
		dmana=30+400/(spells-20); 
		message_vision(HIY "$N"HIY"手捻口诀，念动真言，摇身一变，变得和$n"HIY"一模一样！\n" NOR,me,who);
		who->reply_bian(me);
        	me->set_temp("spellslevel",spells);
		me->set_temp("apply/name",({who->name()}));
    		if(!userp(who)) 
    			me->set_temp("apply/id",who->parse_command_id_list());
		me->set_temp("apply/short", ({who->short()}));
		me->set_temp("apply/long", ({who->long()}));
		me->add("mana",-150);
		if((int)who->query_temp("d_mana")>0) 
		{
	    		me->set_temp("is_living", who->query_temp("is_living"));
	    		me->set_temp("unit",who->query_temp("unit"));
            		me->set_temp("is_character",who->query_temp("is_character"));
	    		me->set_temp("gender",who->query_temp("gender"));
	    		me->set_temp("age",who->query_temp("age"));
	    		me->set_temp("race",who->query_temp("race"));
	    		me->set_temp("family",who->query_temp("family"));
		} 
		else 
		{
            		me->set_temp("is_living",living(who));
	    		me->set_temp("unit",who->query("unit"));
            		me->set_temp("is_character",who->is_character());
	    		me->set_temp("gender",who->query("gender"));
	    		me->set_temp("age",who->query("age"));
	    		me->set_temp("race",who->query("race"));
	    		me->set_temp("family",who->query("family"));
		}
		if( !me->query_temp("d_mana")) 
			call_out("do_bian",5,me);
		me->set_temp("d_mana",dmana);
		me->set_temp("no_heal_up/bian",1);
	}
	return 1;
}

int do_bian(object me)
{  
    	int dmana,mana,spells;

    	if(!me) 
    		return 1;
	dmana=me->query_temp("d_mana");
    	spells=me->query_temp("spellslevel");
	mana=me->query("mana");
    	if( (mana-dmana)>50 && spells>0 && dmana>0) 
    	{
      		me->add("mana",(-dmana));
      		call_out("do_bian",5,me);
    	}
    	else 
    	{
      		mana=mana-dmana;
      		if( mana<20) mana=20;
      		me->set("mana",mana);
      		me->delete_temp("spellslevel");
      		me->delete_temp("d_mana");
      		me->delete_temp("apply/name");
      		me->delete_temp("apply/id");
      		me->delete_temp("apply/short");
      		me->delete_temp("apply/long");
      		me->delete_temp("is_living");
      		while( environment(me)->is_character() )
                	me->move(environment(environment(me)));
      		if( dmana>0) 
        	message_vision(HIY"只见$N"HIY"面色苍白，一个恍惚之间，已经现了原形。\n" NOR,me);
      		me->delete_temp("no_heal_up/bian");
    	}
	return 1;
}

int help(object me)
{
	write(@HELP

指令格式 ： bian [<人物>|<NPC>|<me>]

变身术，这个指令让你变化成其他人物的模样。是否能变，还要取决于
你的法术和法力大小。

其他相关指令： observe。
HELP
	);
	return 1;
}






