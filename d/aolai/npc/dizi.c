inherit NPC;
#include <ansi.h>

void create()
{
        int lvl;
	set_name("武馆弟子", ({"wuguan dizi", "dizi", "trainee","di zi" }) );
	lvl = 1+random(7);
	set_level(lvl);
        set("gender", "男性" );
        set("age", 18+random(10));
        set("long", "一位身材高大的汉子，正在辛苦地操练着。\n");
        set_skill("dodge", lvl*10);
        set_skill("unarmed", lvl*10);
        set_skill("force", lvl*10);
        setup();
	add_money("coin", 100+random(200));
        carry_object("/d/obj/cloth/linen")->wear();
}

void init()
{
	add_action("do_fight","fight");
}

void end_fight(object who,object npc)
{
	int wx,pot;
	if( !who || !npc || !living(who)
	 || !present(who,environment(npc))
	 || !living(npc) 
	 || !who->query_temp("pending/aolai_dizifighting")
	 || who->query_level()>9 )
	 	return;
	who->delete_temp("pending/aolai_dizifighting");
	wx = 1500+random(5000);
	pot = wx/10;
	who->add("combat_exp",wx);
	who->add("potential",pot);
        write( HIW "\n"+name()+HIW"说道：「不打了，不打了，我投降....。」\n\n" NOR);
	tell_object(who,HIY"【系统】通过这轮切磋，你得到了"HIR+wx+HIY"点武学经验和"HIR+pot+HIY"点潜能。\n"NOR);
	who->save();
	who->start_busy(1);
}

int do_fight(string arg)
{
	object who = this_player();
	if( !userp(who) )
		return 0;
	if( !arg || !id(arg) )
		return 0;	
	if( who->query_level()>9 )
		return err_msg("武馆弟子笑道：小的可不是"+RANK_D->query_respect(who)+"的对手。\n");
	if( who->query("kee")<who->query("eff_kee")/10 
	 || who->query("eff_kee")<who->query_maxkee()/10 )
	 	return err_msg("武馆弟子笑道：这位"+RANK_D->query_respect(who)+"还得注意身体。\n");
	if( who->query("sen")<who->query("eff_sen")/10 
	 || who->query("eff_sen")<who->query_maxsen()/10 )
	 	return err_msg("武馆弟子笑道：这位"+RANK_D->query_respect(who)+"还得注意身体。\n");
	if( who->query_temp("pending/aolai_dizifighting") )
		return err_msg("加油加油。\n");	
	if( who->is_busy() )
		return err_msg("你现在正忙着呢。\n");	
        write(HIW"\n你"HIW"对着武馆弟子说道：" + RANK_D->query_self(who) + who->name() + HIW"，领教你的高招！\n"NOR);
        write(HIW+name()+HIW"大喝一声，开始对你发动攻击！\n\n"NOR);
	who->set_temp("pending/aolai_dizifighting",1);
	who->start_call_out( (: call_other, __FILE__, "end_fight", who,this_object():), 3+random(5));
	return 1;
}

void kill_ob(object who)
{
	if( !who ) return ;
	who->remove_killer(this_object());
	this_object()->remove_killer(who);
}

void fight_ob(object who)
{
if( !who ) return ;
who->remove_killer(this_object());
this_object()->remove_killer(who);
}
