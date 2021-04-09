//Cracked by Roath
#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIR+"信件"+NOR, ({"xin jian", "letter","xin"}));
        set("weight", 5);
        if( clonep() )
                set_default_object(__FILE__);
        else {
//                set("long","这是千里眼托付%s的信件，需要将它交给%s的%s。\n");
                set("long","这是千里眼托付的信件。\n");
                set("unit", "个");
                set("no_get", 1);
        }
        set("channel_id", "送宝精灵");
        setup();
}

string job_type(){return "送信任务";}

void init()
{
        add_action("do_give", "give");
}

void set_owner(string owner)
{
        set("owner_id", owner);
}

int do_give(string arg)
{
	mapping job;
	object me,ob;
        string obj,target;
        int i,lvl,qn,exp,dx;
        
        me = this_player();
        if( !query("owner_id") || me->query("id")!=query("owner_id") )
        	return 0;
        if( !arg )
        	return 0;
        if( sscanf(arg,"%s to %s", obj, target)!=2 )
        {
                if(sscanf(arg,"%s %s", target, obj) !=2 )       
                        return 0;
	}
	if(!id(obj) )   
		return 0;
	if( !ob = present(target,environment(me)) )
		return 0;
	if( !me->doing_job("送信任务") )
		return 0;	
	job = me->query_xy_job();
	if( !job || !mapp(job) )
		return 0;
	if( undefinedp(job["送信任务"]) )
		return 0;
	job = job["送信任务"];		
	if( ob->query("name")!=job["target_name"]
	 || ob->query("id")!=job["target_id"] )
		return err_msg("信件不是送给这个人的。\n");
	if( job["target"] )
	{
		if( base_name(ob)!=base_name(job["target"]) )
		{
			ob = job["target"];
			return err_msg("这是给"+MISC_D->find_place(environment(ob))+"的"+ob->short()+"的。\n");
		}
	}	
	if(!living(ob) ) 
                return err_msg(ob->name()+"已经无法收下这样东西了。\n");
	
	message_vision("\n$N拿出一封信件交给了$n。\n",me,ob);
	if( time()>me->query_temp("letter_time") ) 
	{
		message_vision("\n$N打开信件看了看，生气地瞪了$n一眼。\n",ob,me);
                tell_object(me,"你没有及时把信件送到" + ob->name() + "的手中，你的任务失败了！\n");
                if( !me->query_temp("job_cancel_warr") )
                {
                	me->set_temp("job_cancel_warr",1);
                	me->cancel_job("送信任务");
                	me->delete_temp("job_cancel_warr");
                }
                else	me->cancel_job("送信任务");
        } 
        else 
        {
                message_vision("\n$N说道：多谢，多谢！\n",ob,me);
                tell_object(me, "你成功地把信件送到了" + ob->name() + "的手中。\n");
		i = 1000 + ((int)(me->query_temp("letter_time")-time()))*2;
                i+= random(1000);
                if( me->query_level()>=25 )
                	i/= 3;
                exp = i+1000;
                dx = exp/10+1;
                qn = exp/20+1;
                i = 2000+random(1000);
                i = i*3/2;
		QUEST_D->job_reward_player(me,"combat_exp",exp,job_type());
		QUEST_D->job_reward_player(me,"daoxing",qn,job_type());
		QUEST_D->job_reward_player(me,"potential",dx,job_type());
		QUEST_D->job_reward_player(me,"money",i,job_type());
                tell_object(me,HIY+me->finish_job("送信任务",({exp,dx,qn}))+NOR);
                lvl = me->query_job_level("送信任务");
                if( lvl==10 )
                {
                	me->money_add(10000);
                	tell_object(me,HIY"恭喜！你完成了一轮送信任务。\n"NOR);
                	tell_object(me,HIY"【送信】你得到了一两黄金的追加奖励。\n"NOR);
                }
        }
        me->set("jobs/last_letter",time());
        me->delete_temp("letter_time");
        destruct(this_object());
        return 1;
}
