#include <ansi.h>
inherit NPC;

void create()
{
       	set_name("海蛇", ({"hai she","she","snake"}));
	set("long","一条又粗又长的海蛇。\n");
	set("race","野兽");
       	set("gender", "雄性");
	set("attitude", "peaceful");
       	set("shen_type", 1);
        setup();
}

void kill_ob(object who)
{
	tell_object(who,"请珍惜小动物。\n");
	this_object()->remove_all_killer();
	all_inventory(environment())->remove_killer(this_object());
}

void init()
{
	add_action("do_bian","observe");
	add_action("do_bian","look");
}

int do_bian(string arg)
{
	int know;
	object npc,me = this_player();
	string *msgs,str;
	if( !arg || !id(arg) )
		return 0;
	 msgs = ({
        	"脸上露出狡诈的神情，大概又想到了什么坏主意了。",
        	"正在绷着个脸扮酷。","捧着肚子笑得前仰后合。","眉头紧锁，不知在想什么心事。",
        	"咬牙切齿，一副愤愤不平的样子。","一脸的迷茫，不知道周围发生了什么事。","正在咧着嘴傻乐。",
        	"正作天真状。","正在闷闷不乐。","骄傲地昂着头，满脸不屑的神情。","痛苦得呲牙咧嘴，大概是牙痛得厉害。",
        	"正强颜欢笑，但掩饰不住心里的哀伤。","正在眉飞色舞。","一脸的尴尬相。",
        	"脸上露出灿烂的笑容。","笑得比哭还难看。","正强忍着不让自己哭出来。","媚眼如丝。","正作小鸟依人状。",
        	"将身子扭成了一个大大“S”。","将身子扭成了一个大大“B”。",
        	"吐了吐口中长长的口条。",
	});
	if(me->query("mana")<100)
		return err_msg("你的法力不足。\n");
	if( me->is_busy() )
		return err_msg("你现在正忙。\n");	
	me->add("mana",-50);
	me->start_busy(1);
	if( random(10)>8 )
	{
		know = 1;
		str = "却见龙表弟";
	}
	else
	{
	       	str="只见"+name();
       		know=0;
     	}
     	str = "你微一凝神，向"+name()+"细细打量过去。\n"+this_object()->query("long")+str+msgs[random(sizeof(msgs))]+"\n";
     	write(str);
     	if( know==1 )
     	{
     		message_vision(HIY"\n$N"HIY"朝$n"HIY"大喝一声："+RANK_D->query_rude(this_object())+"！快现原形！\n"NOR,me,this_object());
     		message_vision("只见$N浑身松软，瘫倒在地．．．却果然正是龙表弟！\n",this_object());
     		npc = new(__DIR__"biaodi");
     		npc->move(environment());
     		npc->set_skills(me->query_level());
     		npc->kill_ob(me);
     		destruct(this_object());
     		return 1;
     	}
     	return 1;
}

varargs int receive_wound(string type, int damage, object who,mixed attack_type)
{
	damage = 0;
	return ::receive_wound(type, damage, who,attack_type);
}

varargs int receive_damage(string type, int damage, object who,mixed attack_type)
{
	damage = 0;
	return ::receive_damage(type, damage, who,attack_type);
}