// learn.c
#include <ansi.h>
#include <skill.h>
inherit F_CLEAN_UP;

string *reject_msg = ({
        "说道：您太客气了，这怎么敢当？\n",
        "像是受宠若惊一样，说道：请教？这怎么敢当？\n",
        "笑着说道：您见笑了，我这点雕虫小技怎够资格「指点」您什么？\n",
});

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	mapping skills,learned;
        string skill, teacher;
        object ob;
        int master_skill, my_skill,sen_cost,need_p,now_p,qc=0;

        if( !arg || sscanf(arg, "%s from %s", skill, teacher)!=2 )
        	return notify_fail("指令格式：learn <技能> from <某人>\n");
        if( me->is_fighting() )
                return notify_fail("临阵磨枪？来不及啦。\n");
        if(me->is_busy())
		return notify_fail("你正忙着呢。\n");
	now_p = me->query("potential")-me->query("learned_points");	
	if( now_p<1 )
	        return notify_fail("你的潜能已经发挥到极限了，没有办法再成长了。\n");    
	if( !(ob = present(teacher, environment(me))) || !ob->is_character())
        	return notify_fail("你要向谁求教？\n");
        if( !living(ob) )
		return notify_fail("嗯．．．你得先把" + ob->name() + "弄醒再说。\n");
        if( ob->query_skill(skill,2)<1 )
                return notify_fail("嗯．．．这门技能，你还是找会的人学习吧。\n");
        if( !SKILL_D(skill)->valid_learn(me) ) 
        	return 0;
        if( !me->is_apprentice_of(ob) && getuid(ob)!=me->query("couple/id") ) 
        {
		notify_fail( ob ->name() + reject_msg[random(sizeof(reject_msg))] );
                if( (string)me->query("family/family_name") != (string)ob->query("family/family_name")
                 || (int)ob->query("family/privs") != -1 ) 
		{
                	if( !(ob->recognize_apprentice(me)) ) 
                		return 0;
                } 
                else	return 0; // mon add this return 0. 5/6/98
        }
    	if(getuid(ob) == me->query("couple/id") && !userp(ob) )
		return notify_fail("你这个家伙，想干什么？\n");
/*
	if( ob->query_level()<=me->query_level() )
	{
		EMOTE_D->do_emote(ob, "hmm",geteuid(me),CYN,0,0,0); 
		return notify_fail(CYN+ob->name()+CYN+reject_msg[random(sizeof(reject_msg))]);
	}		
*/	
	if( ob->is_fighting())
                return notify_fail("你的师傅暂时没空指点你武功。\n");
        if( !master_skill = ob->query_skill(skill, 1) )
                return notify_fail("这项技能你恐怕必须找别人学了。\n");
        notify_fail(ob->name() + "不愿意教你这项技能。\n");
        if( ob->prevent_learn(me, skill) )
                return 0;
	if( ob->query("env/no_teach") )
                return notify_fail("但是" + ob->name() + "现在并不准备回答你的问题。\n");
	
	skills = me->query_skills();                
	if( !skills || !mapp(skills) || undefinedp(skills[skill]) )
		my_skill = 0;
	else	my_skill = skills[skill];
	if( my_skill>=me->query_level()*10 )
		return notify_fail("你的人物等级过低，已学不了更高的技能了。\n");
	if( userp(ob) )
	{
		if( my_skill<1 )	             
                	return notify_fail("你还是先把基础打好再说吧！\n");
                if( my_skill>=100 )
                	return notify_fail("你已经从"+ob->name()+"身上学不到更多东西了！\n");
	}
	if( master_skill<my_skill )
	{
		message_vision("$N对$n说道："+"你的「"+to_chinese(skill)+"」已经不输为师了，咱们一起切磋切磋吧！"+"\n",ob,me);
		printf("%s和你切磋了一会儿%s，你似乎有所领悟。\n",ob->name(),to_chinese(skill));
		if( my_skill-master_skill<100 )
			need_p = (my_skill+1)*4;
		else if( my_skill-master_skill<200 )
			need_p = (my_skill+1)*5;
		else if( my_skill-master_skill<300 )
			need_p = (my_skill+1)*6;
		else if( my_skill-master_skill<400 )
			need_p = (my_skill+1)*7;
		else if( my_skill-master_skill<500 )
			need_p = (my_skill+1)*8;
		else	need_p = (my_skill+1)*10;	
		qc = 1;
	}
	else	need_p = (my_skill+1)*3;
	learned = me->query_learned();
	if( learned && mapp(learned) && !undefinedp(learned[skill]) )
		need_p-= learned[skill];
	if( need_p<1 )
		need_p = 1;
	if( now_p<need_p )
		return notify_fail("你要将「"+to_chinese(skill)+"」提高至 "+(my_skill+1)+" 级，需要潜能 "+need_p+" 点，你目前的潜能仅有 "+now_p+" 。\n");
	sen_cost = 100-me->query_int();
	if( sen_cost>60 )
		sen_cost = 60;
	if( sen_cost<10 )
		sen_cost = 10;	
	sen_cost+= (need_p/10+1);	
	if( me->query("sen")<sen_cost )
		return 	notify_fail("你的精神不够"+sen_cost+"。\n");
	if( userp(ob) && ob->query("sen")<sen_cost )
		return 	notify_fail(ob->name()+"今天太累了，结果你什么也没有学到。\n");	
	if( !userp(ob) && ob->query("sen")<sen_cost/10+1 )
		return 	notify_fail(ob->name()+"今天太累了，结果你什么也没有学到。\n");	
		
	if( qc==0 )
	{
		printf("你向%s请教有关「%s」的疑问。\n", ob->name(),to_chinese(skill));
		printf("你听了%s的指导，似乎有些心得。\n", ob->name());
	}	
	my_skill+= 1;
	me->add("potential",-need_p);
	tell_object(me,HIY"【系统】你的潜能减少了"HIR+need_p+HIY"点。"NOR"\n");
	if( !skills || !mapp(skills) )
		me->set_skill(skill,1);
	else	skills[skill ] = my_skill;
	if( learned && mapp(learned) && !undefinedp(learned[skill]) )
		map_delete(learned,skill);
	me->save(1);
	me->receive_damage("sen", sen_cost );
	if( userp(ob) )
		ob->receive_damage("sen", sen_cost );
	printf(HIC"你的「%s」升至 %d 级。\n"NOR, to_chinese(skill),my_skill);	
	return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : learn|xue <技能> from <某人>
 
这个指令可以让你向别人请教有关某一种技能的疑难问题，当然，你请教的对象在这
项技能上的造诣必须比你高，而你经由这种方式学习得来的技能也不可能高于你所请
教的人，然而因为这种学习方式相当于一种「经验的传承」，因此学习可以说是熟悉
一种新技能最快的方法。

通常，一个人刚学到一种新技能是不会有什么疑难问题的，而是经由实际上的应用中
遭遇问题，这些问题对于学习一种新技能的过程是很重要的，尤其是各种作为其他技
能基础的基本技能，更需要经由「发现问题─解决问题」的过程才能得到较好的效果
因此我们将这种发现问题的过程用「潜能」的观念表示，一个人能够自己发现某些问
题，表示他(她)有解决这项问题的潜能，当你具有这样的潜能时就可以利用这个指令
来向其他人请教，而获得进步。
(PS. 潜能还有其他更广义的定义，这里只是其中之一 )

此外学习也需要消耗一些精力，而消耗的精力跟你自己、与你学习对象的悟性有关。

至于如何知道你能从对方学到什么技能，如果对方是你的师父，可以用 skills 指令
直接查看，如果不是你的师父，那么通常会有其他的提示，你只好自己想办法。

其他相关指令 : practice、study
HELP
        );
        return 1;
}
