#include <ansi.h>
inherit ROOM;

string *msg=({
	"我闻佛音声，世所未曾有，所言真实者，应当修供养。","仰惟佛世尊，普为世间出，亦应垂哀愍，必令我得见。",
	"即生此念时，佛于空中现，普放净光明，显示无比身。","胜鬘及眷属，头面接足礼，咸以清净心，叹佛实功德。",
	"如来妙色身，世间无与等，无比不思议，是故今敬礼。","如来色无尽，智慧亦复然，一切法常住，是故我归依。",
	"降伏心过恶，及与身四种，已到难伏地，是故礼法王。","知一切尔焰，智慧身自在，摄持一切法，是故今敬礼。",
	"敬礼过称量，敬礼无譬类，敬礼无边法，敬礼难思议。","哀愍覆护我，令法种增长，此世及后生，愿佛常摄受。",
	"我久安立汝，前世已开觉，今复摄受汝，未来生亦然。","我已作功德，现在及余世，如是众善本，惟愿见摄受。"
});

string *msg2_1 = ({
	"一道寒风掠过，",
	"寒风呼呼的吹，",
	"寒风怒号，",
	"一阵冷风吹过，",
});	
string *msg2_2 = ({
	"只觉扑面寒风刮骨般的疼。。。。\n",
	"洞内的温度骤然一降。。。。\n",
	"引得洞内温度骤降。。。\n",
});
	
void msgs(object me)
{
	if( !me || !me->query_temp("xiulian") ) 
		return;
	if( !living(me) || !present(me,this_object()) )
	{
		me->delete_temp("xiulian");
		return;
	}
	tell_object(me,msg2_1[random(sizeof(msg2_1))]+msg2_2[random(sizeof(msg2_2))]);
	me->receive_damage("kee",80+random(30),me);
	me->add("mana",-100);
	if( me->query("kee")<150 || me->query("mana")<100 )
	{
		call_out("lian_fail",1,me);
		return;	
	}
	if( me->query_temp("xiulian") )
        {
        	tell_object(me,"冥冥中，你耳边好似有佛偈之音："+msg[random(sizeof(msg))]+"\n");
        	if( me->query("class")=="bonze" )
        		tell_object(me,"你越发虔诚。\n");
        	else	tell_object(me,"你不胜其烦，也只能静下心来，不敢为其所惑。\n");	
        	if( random(10)>4 )
        	{
        		if( random(me->query_cps()/10)>=5 && random(4)==1 )
        		{
        			call_out("lian_succ",1,me);
        			return;
        		}
        		else
        		{
        			call_out("lian_fail",1,me);
        			return;
        		}
        	}
        	else	call_out("msgs",5+random(5),me);
        }
}

void create ()
{
        set ("short", HIW"灵鹫洞"NOR);
        set ("long", HIW+@LONG
整个山洞都是白雪堆积而成，周围除了白色还是白色，你来到这
里，心里感到前所未有的清净，不愧为佛家修炼的无上宝境，据说当
年如来佛祖就是在这里修炼成丈六金身的。

LONG+NOR);
        set("exits",([
                "down" : __DIR__"no4-enter",
        ]));
	setup();
}

void init()
{
        add_action("do_xiulian", "xiulian");
}

int do_xiulian()
{       
	int level,mana,i;
        object me=this_player();
        if( me->is_busy() ) 
        	return err_msg("你正忙着呢！\n");
        if( me->query_temp("xiulian") ) 
        	return err_msg("你已经在修炼了！\n");
        if( me->query("sen")<100 )
        	return err_msg("你现在精神萎靡，如何能静下心来修炼？\n");
        if( me->query("mana")<100 )
        	return err_msg("你法力不够充沛，无法修炼。\n");
        if( ((int)me->query("potential")-(int)me->query("learned_points"))<500 )
        	return err_msg("你的潜能不足了。\n");
        if( !wizardp(me) && time()<me->query("family/dingshen_fail")+60 )
        	return err_msg("你刚刚失败过，还是静下心思再来吧。\n");
        me->set_temp("xiulian",1);
        me->add("potential",-500);
        me->add("mana",-100);
        me->receive_damage("sen",100,me);
	tell_object(me,"你开始静坐修炼。\n");
	me->start_busy(100);
        call_out("msgs",1,me);
        return 1;
}

void lian_fail(object me)
{
        if( !me )
        	return;
        if( !living(me) || !present(me,this_object()) )
	{
		me->delete_temp("xiulian");
		return;
	}
	tell_object(me,"你心神一阵不宁，难以维持冥思状态，慌忙退出了修炼。\n");
	tell_object(me,"侥幸元神未受到伤害，你吓出了一身冷汗。\n");
	me->set("family/dingshen_fail",time());
	me->delete_temp("xiulian");
	me->start_busy(1);
	if( me->query("family/family_name")=="方寸山三星洞"
	 && !me->is_knowing("puti_dingshen") )
		tell_object(me,HIY"【领悟】你领悟「"HIR"定身咒"HIY"」失败！"NOR"\n\n");
}

void lian_succ(object me)
{
	if( !me )
		return;
	if( !living(me) || !present(me,this_object()) )
	{
		me->delete_temp("xiulian");
		return;
	}
	me->start_busy(1);
	if( me->query("class")=="bonze" )
		me->improve_skill("buddhism",random(200)+me->query_int(),1);
	tell_object(me,"你修炼完毕，感觉自己的领悟到了另一个境界。\n");
	me->improve_skill("spells",random(100)+me->query_int(),1);
	
	if( me->query("family/family_name")=="方寸山三星洞"
	 && !me->is_knowing("puti_dingshen") )
	{
		me->delete_temp("xiulian");
		CHANNEL_D->do_channel(this_object(),"rumor","听说"HIY+me->name()+HIM"领悟了三星洞绝学「"HIY"定身咒"HIM"」！"NOR);
		me->set_knowing("puti_dingshen",1);
		me->save();
	}
}	

int valid_leave(object me, string dir)
{
	if(dir=="down"&&me->query_temp("xiulian") )
 		return notify_fail("你还是先修炼完了再走吧。\n");
    	return ::valid_leave(me, dir);
}
