//jobs.c
#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object who;
	mapping job;
	int i,f,s,n;
	string msg,*types = ({
		"李靖任务","解密任务","门派任务","袁天罡任务","如来任务","送信任务","寻宝任务","分配任务","押镖任务","守城任务","杀手任务",
	});	
	
	if( !arg || !wizardp(me) )
		who = me;
	else if( !arg )
		who = me;
	else
	{
		who = find_player(arg);
		if( !who )
			return notify_fail("没有这个人。\n");
	}
	
	job = who->query_xy_job();
	if( !job || !mapp(job) )
		return notify_fail((who==me?"你":"他")+"还没有开始做任务。\n");
	
	arg = (who==me?"你":who->name(1))+"的任务列表：\n";
	
	for(i=0;i<sizeof(types);i++)
	{
		job = who->query_xy_job();
		arg+= "  "HIY"【"HIG+types[i]+HIY"】"NOR;
		if( !undefinedp(job[types[i]]) )
		{
			job = job[types[i]];
			s = job["succ"];
			f = job["fail"];
			n = s+f;
			if( n<1 ) n = 1;
			arg+= "\n";
			arg+= "         完成：成功"HIY+s+NOR"个 失败"HIY+f+NOR"个 总计"HIY+n+NOR"个，成功率"HIR+s*100/n+NOR"%\n";
			if( !undefinedp(job["exp"]) && job["exp"]>0 )
				arg+= "         上次奖励："+HIY+job["exp"]+NOR"经验 "HIY+COMBAT_D->chinese_daoxing(job["daoxing"])+NOR"道行 "HIY+job["pot"]+NOR"潜能\n";
			if( !who->doing_job(types[i]) ) 
				arg+= "         目前进度："WHT"暂无任务"NOR"\n";
			else
			{
				msg = job["msg"];
				msg = COLOR_D->clean_color(msg);
				if( strsrch(msg,"\n")==-1 )
					msg+= "\n";
				arg+= "         目前进度："+msg;
				arg+= "         任务等级：第"HIR+who->query_job_level(types[i])+NOR"个\n";
			}	
		}
		else	arg+= "未有建树\n";
		arg+= "\n";
	}	
	me->start_more(arg);
	return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : jobs
 
这个指令可以显示目前支持的全局任务中，你完成的情况。
 
HELP
    );
    return 1;
}

