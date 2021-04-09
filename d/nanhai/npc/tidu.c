//Cracked by Roath
// tidu.c
#include <ansi.h>
inherit SUPER_NPC;

string ask_for_join();
string ask_for_leave();
string ask_for_huansu();

void create()
{
	set_name("剃度僧", ({ "tidu seng", "seng" }) );
	create_family("南海普陀山", 4, "弟子");
	set("title","普陀山执事");	
      	set_level(50);
	set("gender", "男性");
	set("age", 50);
	set("attitude", "peaceful");
	set("class", "bonze");
	set("force_factor", 5);
	set("mana_factor", 115);

	set("inquiry", ([
		"剃度" : (: ask_for_join :),
		"出家" : (: ask_for_join :),
		"还俗" : (: ask_for_huansu :),
		"脱离" : (: ask_for_leave :),
           	"leave" : (: ask_for_leave :),
	]) );

	set_skill("staff",500);
	set_skill("unarmed",500);
	set_skill("force",500);
	set_skill("dodge",500);
	set_skill("literate",500);
	set_skill("parry",500);
	set_skill("spells",500);
	set_skill("lotusforce",500);
	set_skill("buddhism",500);
	set_skill("lunhui-zhang",500);
	set_skill("lotusmove",500);
	
	map_skill("dodge","lotusmove");
	map_skill("force", "lotusforce");
	map_skill("spells", "buddhism");
	map_skill("parry","lunhui-zhang");
	map_skill("staff","lunhui-zhang");
	
	set_skill("bubu-shenglian",500);
	
	set("env/test","HIB");
	set("weapon_level",40);
	set("armor_level",40);
	setup();
	carry_object(0,"staff",1)->wield();
	carry_object(0,"shoes",1)->wear();
	carry_object(0,"pifeng",1)->wear();
	carry_object("/d/nanhai/obj/sengpao")->wear();
	powerup(0,1);
}

void init()
{
	add_action("do_kneel", "kneel");
        add_action("do_agree", "agree");
        add_action("do_huansu", "huansu");
}

string ask_for_huansu()
{
	object me;

	me = this_player();

	if( (string)me->query("bonze/class")!="bonze" )
		return "阿弥陀佛！你既已身系尘世，何必凑这个热闹？\n";
	me->set_temp("pending/leave_bonze", 1);
	tell_object(me,CYN+name()+CYN"说道：阿弥陀佛！一入俗世，万劫不复，"+RANK_D->query_respect(me)+"一身佛法也将随之付诸东流。还望"+RANK_D->query_respect(me)+"三思。\n"NOR);
	return RANK_D->query_respect(me)+"若已决定，便请脱袍还俗(huansu)。\n";
}

int do_huansu()
{
        if( !this_player()->query_temp("pending/leave_bonze") ) 
        	return 0;
	message_vision( HIC "$N"HIC"脱下身上的袈裟，恭恭敬敬地跪下来磕了几个响头，从此恢复了自由身。\n\n"NOR, this_player(), this_object() );
	//this_player()->delete("class");
	this_player()->delete("bonze/class");
	this_player()->delete_skill("buddhism");
	tell_object(this_player(),CYN+name()+CYN"说道：从今以後你恢复出家前的俗名「"NOR HIC+this_player()->query("bonze/old_name")+NOR CYN"」吧。"NOR"\n");
	this_player()->set("name", this_player()->query("bonze/old_name") );
	EMOTE_D->do_emote(this_object(), "sigh",geteuid(this_player()),CYN,0,0,0);
        this_player()->delete_temp("pending/leave_bonze");
	this_player()->save();
	return 1;
}

string ask_for_join()
{
	object me;
	me = this_player();
	if( me->query("married") )
		return "阿弥陀佛！施主有了家庭拖累，想必难以潜心向佛。\n";
	if( (string)me->query("bonze/class")=="bonze" )
		return "阿弥陀佛！你我同是出家人，何故跟老衲开这等玩笑？\n";
	if( me->query("bonze/justonetime") )
		return "施主既已还俗，又何苦再次出家？\n";
	me->set_temp("pending/join_bonze", 1);
	return "阿弥陀佛！善哉！善哉！施主若真心皈依我佛，请跪下(kneel)受戒。\n";
}

int do_kneel()
{
	int i;
	object me = this_player();
	string *prename,name, new_name;
	mapping names;	 

	if( !this_player()->query_temp("pending/join_bonze") ) 
		return 0;
	message_vision(	HIC "$N"HIC"双手合十，恭恭敬敬地跪了下来。\n\n$n"HIC"伸出手掌，在$N"HIC"头顶轻轻地摩挲了几下，将$P的头发尽数剃去。\n\n" NOR,this_player(), this_object() );

	name = this_player()->query("name");
	if( me->query("gender")=="女性" )
		prename = ({ "文", "净", "方", "慧" });	
	else	prename = ({ "空", "明", "虚", "法" });
	i = me->query("family/generation");
	if( i<=0 )
		i = (this_object()->query_level()-me->query_level())/10;
	else	i = i-query("family/generation")+2;
	if( i<0 ) i = 0;
	if( i>3 ) i = 3;
	new_name = prename[i];
	names = NAME_D->random_name2((me->query("gender")=="女性"?1:0), -1, new_name, 0, 0);
	new_name = names["name"];
	
	CHANNEL_D->do_channel(this_object(),"chat","近日，"+me->query("name")+"于我南海观世音道场，归化三宝，行灌顶之仪，佛名「"+new_name+"」。");
	EMOTE_D->do_emote(this_object(), "smile",geteuid(this_player()),CYN,0,0,0);
	me->delete_temp("pending/join_bonze");
	me->set("name", new_name);
	me->set("bonze/class", "bonze");
	me->set("bonze/justonetime", 1);
	me->set("bonze/old_name", name);
        //me->set("class", "bonze");
	me->save();
	return 1;
}

string ask_for_leave()
{
	object me=this_player();
	if( (string)me->query("bonze/class")=="bonze" )
		return "阿弥陀佛，汝如执意下山，先得脱离吾佛教，还俗后再来。\n";
	if( me->query("family/family_name") == "南海普陀山" ) {
		command("say 你既是执意下山，贫僧却有几句话说。");
		me->set_temp("betray", "putuo");
		return ("脱离师门要需要有一定惩罚，你可愿意(agree)?\n");
	}
	return ("贫僧不知。\n");
}
	
			
int do_agree(string arg)
{
	if( this_player()->query_temp("betray")!="putuo" )
		return 0;
	if( this_player()->query("family/family_name") != "南海普陀山")
		return 0;
	if( FAMILY_D->leave_family(this_player(),this_object()) )
	{		
		message_vision("$N答道：弟子愿意。\n\n", this_player());
		command("say 既是你与佛门无缘，你便下山去吧！\n");
		command("say 江湖风波，善恶无形，好自为之。。。\n");
		return 1;
	}
	return 0;
}