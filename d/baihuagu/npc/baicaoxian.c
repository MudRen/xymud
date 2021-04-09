inherit SUPER_NPC;
#include <ansi.h>

string ask_mieyao();
string ask_cancel();
string ask_for_leave();
string home_me();
string check_class();
string shilian();
mixed about_zongheng();

void create()
{
	set_name("百草仙", ({"baicao xian","xian"}));
	set_level(80);
	set("long","百花谷总管。\n");
	create_family("百花谷",3, "弟子");
	set("title", "门派接引使");
	set("nickname","百花谷");
	set("gender", "男性");
	set("age", 35);
	set("attitude", "friendly");
	set_skill("literate",800);
	set_skill("unarmed", 800);
	set_skill("dodge",800);
	set_skill("force",800);
	set_skill("parry", 800);
	set_skill("sword", 800);
	set_skill("spells", 800);
	set_skill("zongheng-sword",800);
	set_skill("siji-zhang", 800);
	map_skill("sword", "zongheng-sword");
	set_skill("baihua-xianfa", 800);
   	set_skill("brightjade-force", 800);
   	set_skill("rainbow-zhi",800);
   	set_skill("wuyou-steps", 800);
   	map_skill("unarmed", "rainbow-zhi");
   	map_skill("parry", "zongheng-sword");
   	map_skill("force", "brightjade-force");
   	map_skill("dodge", "wuyou-steps");
   	set_skill("jiefeng",800);
   	set("env/test","HIB");
   	set("inquiry", ([
	   	"kill": (: ask_mieyao :),
	   	"师门任务": (: ask_mieyao :),
	    	"cancel": (: ask_cancel :),
	    	"出山" : (: ask_for_leave :),
		"leave" : (: ask_for_leave :),
		"返回师门"  : (: home_me :),
		"带艺拜师" : (: check_class :),
		"重悟纵横" : (: about_zongheng :),
	]));  
	setup();
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"shoes",1)->wear();
	carry_object(0,"sword",1)->wield();
	powerup(0,1);
}

void init()
{
	 add_action("do_agree", "agree");
}

mixed about_zongheng()
{
	int need,num,base = 500000;
	object me = this_player();
	if( me->query("family/family_name")!="百花谷" )
		return 0;
	if( me->query_level()<25 )
		return "好好修炼，这些高级功法不是你所能领悟的。";
	if( me->is_knowing("bhg_zongheng")<=0 )
		return "你先去找掌门寻回剑谱吧。";
	num = me->query("mark/zongheng_re");
	need = base+num*100000;	
	if( me->query("faith")<need )
		return "你还是下去多为师门做贡献，待师门贡献达到"NOR HIR+need+NOR CYN"再来问我。";
	EMOTE_D->do_emote(this_object(), "hmm",geteuid(me),CYN,0,0,0);
	tell_object(me,CYN+name()+CYN"说道：既然你想重新领悟「"NOR HIC"纵横剑法"NOR CYN"」的奥妙，老夫便给你找个机会。"NOR"\n");
	tell_object(me,HIW+name()+NOR HIW"正盯着你看，不知道打些什么主意。\n"NOR);
	tell_object(me,HIC+name()+NOR HIC"念叨了几句咒语，伸手在你头顶一抚，你顿时觉得脑海一空，好似是忘记了什么。。。。\n"NOR);
	me->add("faith",-need);
	me->add("mark/zongheng_re",1);
	me->delete("bhg");
	me->delete_knowing("bhg_zongheng");
	me->save();
	tell_object(me,HIG"【师门】你清除了纵横剑法的领悟。\n"NOR);
	tell_object(me,HIY"【系统】你失去了"HIR+need+HIY"点师门贡献。\n"NOR);
	EMOTE_D->do_emote(this_object(), "ok",geteuid(me),CYN,0,0,0);
	return 1;		
}

void attempt_apprentice(object ob)
{
	if( ob->query_level()>=85 )
	{
        	EMOTE_D->do_emote(this_object(), "wow",geteuid(ob),CYN,0,0,0);
           	tell_object(ob,CYN+name()+CYN"说道：这位"+RANK_D->query_respect(ob)+"还是去找孔雀仙君吧。\n"NOR);
           	return ;
	}	
	EMOTE_D->do_emote(this_object(), "pat",geteuid(ob),CYN,0,0,0);
	tell_object(ob,CYN+name()+CYN"说道：好，希望" + RANK_D->query_respect(ob) +"多加努力，把我们百花谷发扬光大。\n"NOR);
	command("recruit " + geteuid(ob) );
	CHANNEL_D->do_channel(this_object(),"chat","百花谷又多了一个弟子  "+ob->name(1)+HIW"\n				     百花谷的势力加强了。\n"NOR);
	return;
}

int recruit_apprentice(object ob)
{
	 if( ::recruit_apprentice(ob) )
	 	ob->set("class","xian");
}

string ask_mieyao()
{
    	object who=this_player();
        if( who->query_level()<20 )
                return "师门任务 20 级才开放。";
    	if((string)who->query("family/family_name")=="百花谷") 
    	{
      		EMOTE_D->do_emote(this_object(), ({"addoil","touch","ok"})[random(3)],geteuid(who),CYN,0,0,0);
      		return "/quest/family/mieyao"->query_yao(who);
    	}
    	return ("非我门人,何故来此?\n");
}

string ask_cancel()
{
	if( this_player()->query("family/family_name")!="百花谷" )
		return 0;
	return "/quest/family/mieyao"->cancel_me(this_player());	
}

string ask_for_leave()
{
	object me=this_player();

	if (me->query("family/family_name") == "百花谷" ) 
	{
		if( me->query_level()<40 )
			return "你个外门弟子，也想下山？";
		command("say 你既是执意下山，我却有几句话说。");
		me->set_temp("betray", "baihuagu");
		return ("脱离师门要需要有一定惩罚，你可愿意(agree)？");
	}

	return 0;
}

int do_agree(string arg)
{
	if( this_player()->query_temp("betray")=="baihuagu"
	 && this_player()->query("family/family_name") == "百花谷" )
	{
		if( FAMILY_D->leave_family(this_player(),this_object()) )
		{
			message_vision("$N答道：弟子愿意。\n\n", this_player());
			command("say 既是你与百花谷无缘，你便下山去吧！");
			return 1;
		}
	}
	return 0;
}

string home_me()
{
	string str;
	object me = this_player();
	if( me->is_busy() || me->is_fighting() )
		return "。。。。";
	if( this_object()->is_busy()
	 || this_object()->is_fighting() )
		return "等等，我现在抽身不得。";
	if( me->query("family/family_name")!="百花谷" )
		return 0;	
	str = "/d/baihuagu/huahai";
	message_vision("$N朝$n点了点头。\n\n",this_object(),me);
	this_object()->start_busy(1+random(2));
	me->move(str,2);
	tell_object(me,"\n\n你眼前一花，已被传回了师门。\n");
	return "....";
}

int prevent_learn(object who,string skill)
{
	if( skill!="zongheng-sword" )
                return 0;
	if( who && userp(who) && who->is_knowing("bhg_zongheng")>0 )
                return 0;
	tell_object(who,query("name")+"说道：你是从哪里得来的纵横剑法？\n");
	return 1;
}

string check_class()
{
	int num;
	object me = this_player();
	if( me->query("family/family_name") )
		return "这位"+RANK_D->query_respect(me)+"说笑了。";
	if( me->query_level()<40 )
		return RANK_D->query_respect(me)+"，我看你骨骼精奇，算不上万中无一的奇才，但也非碌碌之辈，便收你为徒如何？"; 
	if( me->query("class")=="xian" )
		return "欢迎这位道友入我百花谷，真乃蓬荜生辉。";
	if( me->query_temp("pendding/bhg_class") )
	{
		EMOTE_D->do_emote(this_object(), "wow",geteuid(me),CYN,0,0,0);
		return "这位"+RANK_D->query_respect(me)+"事不宜迟，赶紧寻合适的师傅便拜了吧。";
	}
	if( me->query("family/kill_moon_need")>0 )
	{
		EMOTE_D->do_emote(this_object(), "addoil",geteuid(me),CYN,0,0,0);
		return "事情办的怎么样了。";
	}
	num = 5;
	num+= me->query_level()/5;
	me->set("family/kill_moon_need",num);
	message_vision("$N恨恨言道：当初王母寿诞，若不是嫦娥从中作梗，吾谷百花仙子怎会与王母有隙。现如今她嫦娥既然在人间开宗结派，吾百花谷自不能落于其后。奈何其占据昆仑古墟，吾等虽有蓬莱仙岛一隅，然修行非一日之功。盖日积月累，弥逊尔一筹也。真是气煞吾等。\n",this_object());
	command("whisper "+me->query("id")+" 为今之计，唯有行非常手段，你且去刺杀"+chinese_number(num)+"位月宫弟子，以解吾心头之恨！\n");
	tell_object(me,HIR"【师门】此任务杀玩家无效。\n"NOR);
	return "切不可生那杀生之心，夺了初修道者性命。切记切记！";
}
