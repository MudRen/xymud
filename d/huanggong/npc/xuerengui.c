inherit NPC;
#include <ansi.h>
#include <greeting.h>
string ask_bad(object me);
int do_job();
int ask_done();
int ask_que();

string about_qingling()
{
	object me = this_player();
	if( me->query_temp("maze/qingling_ask") )
		return "多说无益，你去看看吧。";
        if( time()<me->query("maze/qingling")+1800 )
		return "你还是下去歇歇再去吧。";
	me->set_temp("maze/qingling_ask",1);
	return "好，便依赖"+ RANK_D->query_respect(me)+"了。";	
}

void create()
{
	set_name("薛仁贵", ({ "xue rengui", "xue", "rengui" }) );
	set_level(39);
	set("gender", "男性");
	set("age", 35);
	set("long","薛仁贵是长安城九门提督，负责皇宫内外安全。\n");
	create_family("将军府",3,"元帅");
	set("title", HIR"征东大元帅"NOR);
	set("nickname", HIY"勇冠三军"NOR);
	set("attitude", "friendly");
	set("force_factor", 100);
	set("mana_factor", 100);
	
	set_skill("unarmed",390);
        set_skill("force",390);
        set_skill("dodge",390);
        set_skill("parry",390);
        set_skill("spear",390);
        set_skill("bawang-qiang",390);
        map_skill("spear","bawang-qiang");
        map_skill("parry","bawang-qiang");
        set_skill("lengquan-force",370);
        map_skill("force","lengquan-force");
        set_skill("yanxing-steps",370);
        map_skill("dodge","yanxing-steps");
	set("inquiry", ([
	/*
        "逃犯": (: ask_bad :),
        "平乱炔": (: ask_que :),
        "que": (: ask_que :),
        "守城" : (: do_job :),
        "job"  : (: do_job :),
        "完成" : (: ask_done    :),
        "done" : (: ask_done    :),
        */
        	"始皇陵" : (: about_qingling :),
	]));
	set("chat_chance_combat", 50);
	set("chat_msg_combat", ({
                (: perform_action, "spear", "ba" :),
                (: perform_action, "spear", "bugong" :),
                (: perform_action, "spear", "huima" :),                
                (: perform_action, "spear", "juanlian" :),                
	}) );
	set_temp("weapon_level",10+random(20));
	set_temp("armor_level",10+random(20));
	set("env/test","HIY");
	setup();
	carry_object(0,"armor",1)->wear();
	carry_object(0,"shoes",1)->wear();
	carry_object(0,"kui",1)->wear();
	carry_object(0,"pifeng",1)->wear();
	carry_object(0,"shield",1)->wear();
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"spear",1)->wield();

}

void init ()
{
greeting2(this_player());
}

int accept_fight(object me)
{
command("say 我为殿前将军，岂能与你村野匹夫较艺！");
return 0;
}

int ask_que()
{ 
        object ob,me;
        me=this_player();
        if( me->query_temp("queget") == 1 )
           return notify_fail("你又糊涂了。\n"); 
        if ( me->query("office_number") > 250 )    {
            command("say 为朝廷除乱有功，皇上特赐平乱炔！\n");
          ob=new("d/obj/suburb/que");
          ob->move(this_player()); 
          me->set_temp("queget", 1);
        message_vision("\n$N给了$n一枚平乱炔。\n",  this_object(),this_player());
         return 1;            }
         else
         {command("say 还得加油为朝廷除乱！\n");
         command("pat " + me->query("id"));
          ob=new("d/obj/suburb/rose");
          ob->move(this_player()); 
          me->set_temp("queget", 1);
        message_vision("\n$N给了$n一支红玫瑰。\n",  this_object(),this_player());
         return 1;           
            }
      return 0;
}


string ask_bad(object me)
{
    me=this_player();
    if ( me->query("office_number") > 300 )
        return ("不敢有劳大驾。");
    if(me->query("combat_exp") < 100000 )
        return ("我怎么能放心你去呢？");
    return "/d/obj/bad"->query_yao(me);
}

int accept_object(object who, object ob)
{
                int i;
      string bname = who->name()+"的"+who->query("bad/name") + "的头颅";
     
     if ( (string)ob->query("name") != bname )
        return notify_fail("薛仁贵怒道：你竟敢糊弄我！\n");
        
if (!ob->query("killer") ||ob->query("killer") != who->query("id"))
       return notify_fail("薛仁贵大怒：不是你杀的也敢拿来,小心我扁你！\n");
                i =who->query("combat_exp");
      who->add("office_number", 1);
      who->money_add(5000);
      tell_object(who,HIG"【星月任务】你得到了五十两白银。\n"NOR);
      TASK_D->job_reward_player(who,"combat_exp",1501,"守城任务");
	TASK_D->job_reward_player(who,"potential",(50 + random(100)),"守城任务");
      command("smile");
           command("pat " + who->query("id"));
      tell_object(who,"薛仁贵点点头：不错，应该奖励。\n");
//message("channel:chat",HIY+"【大唐天朝】薛仁贵(Xue rengui)："+who->query("name")+"杀死了"+who->query("bad/name")+"，功加一等。\n"+NOR,users());
      who->delete("bad");
      return 1;
}

int do_job()
{      
        object me;
        me = this_player(); 
        
    if( me->query("job/sxy-done")>0)
    {
                tell_object(me,"你必须先把上次的任务报告了以后才能再要任务。\n");
                return 1;
    } 
    else 
    if( me->queryi("job/sxy")>0)
    {
                tell_object(me,"你已在这儿要过任务了，快去守城。\n");
                return 1;
    } 
    else 
    if( me->query("combat_exp")<60000)
    {
                tell_object(me,"你为朝廷效力之心可表，可是守城不是儿戏，不要丢了性命。\n");
                return 1;
    }

    message_vision(CYN"薛仁贵对$N说道：你这就去吧，为朝廷效力，才是升官捷径者。\n"NOR,me); 
        me->set("job/sxy", 1);
        me->apply_condition("sxy-job", 8);
        return 1;   
}

int ask_done()
{      

        object me,ob;
        int gong,exp,pot,money;
        me = this_player();
        gong = me->query("job/gong");
        exp = gong * 100;
        pot = gong * 30;
        money = gong * 100; 
        
    if( me->query("job/sxy-done")< 1)
    {
                tell_object(me,"你的任务还没完成呢。\n");
                return 1;
    }

    message_vision(CYN"薛人贵对$N说道：做得不错！为国出力就应如此。\n"NOR,me);
    message_vision(CYN"薛仁贵对$N说道：你总共立了" + gong + "件功。\n"NOR,me);     
    message_vision(CYN"薛仁贵对$N说道：该奖励你" + exp + "点经验，" + pot + "点潜能，" + money + "两银子，"+gong + "点官值。\n"NOR,me);        
    me->add("combat_exp",exp);
    me->add("potential",pot);
    me->add("office_number",gong);
    me->delete("job/gong");
    me->delete("job/sxy");
    me->delete("job/sxy-done");
    ob=new("/clone/money/silver");
    ob->set_amount(money);
    ob->move(me);
    return 1;
}

void unconcious()
{
die();
}
void die ()
{
	powerup(0,1);
}
