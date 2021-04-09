// 凤凰涅磐
//lestat for 雪山
#include <ansi.h>

int cast(object me, object target)
{
        int t,bt,cost;
	string msg;
	
	if( me->query_level()<40 )
		return notify_fail("你的人物等级不够。\n");
	t = me->query_skill("fenghuang-xuemai",1);
	t = t/60;
	if( t>15 )
		t = 15;
	t = 30-t;
	if( time()-(int)me->query_temp("xiao_end")<t )
        	return notify_fail("你刚浴火重生了！\n");
	if( me->query("family/family_name") != "大雪山" )
                return notify_fail("你不是飞禽，无法浴火重生。\n");
      	if( !me->is_fighting() )
        	return notify_fail("凤凰涅磐只能在战斗中使用！\n");
        if( me->query("mana")<500 )
		return notify_fail("你的法力不够。\n");
	if( me->query_skill("dengxian-dafa",1)<400 )
		return notify_fail("你的登仙大法不够娴熟。\n");
	if((int)me->query("faith") < 100  )
                return notify_fail("你在雪山时日尚浅，不能有效施展「凤凰涅磐」！\n");		
	bt = random(8-me->query_kar()/5);
	if( bt<3 )
		bt = 3;
        cost = 500;
        if( (int)me->query("eff_kee") < (int)me->query("max_kee") / 2 )
		cost = cost/2;

	message_vision(BLU"\n$N"BLU"神色惨淡，伸手打开发髻，长发下垂，覆在脸上，跟着点燃红磷粉，咬破舌尖，一口"RED"鲜血"BLU"喷出。嗤嗤两声轻响，爆出几朵火花，"HIR"火花"BLU"忽地一暗，随即大为明亮。\n"NOR,me,target);
	message_combatd(HIW"\n此时$N"HIW"脸上已无半点血色，一口口鲜血不住向"NOR RED"火焰"NOR HIW"中吐去 ，火势越来越猛!!\n"NOR,me,target);
	message_combatd(HIR"\n随即，$N"HIR"念了几句咒语，猛地身子急旋，如陀螺般连转了十多个圈子，接着大袖拂动，整个火焰堆陡地拨起，凌空燃烧，便如一座"NOR RED"火墙"NOR HIR"般，夹着排山倒海之势将$P吞没！\n"NOR,me,target);
	message_combatd(HIR"\n但听一声凤鸣，一只"HIY"彩凤"HIR"从火焰中冲天而起，一片片羽毛从空中雪花般飘落，$N"HIR"缓缓落下，全身上下焕然一新！\n"NOR,me,target);
	
	me->start_busy(bt);
        me->add("mana", -cost);
        me->set("eff_kee",me->query_maxkee());
        me->set("eff_sen",me->query_maxsen());
        me->set("kee",me->query("eff_kee"));
        me->set("sen",me->query("eff_sen"));
        me->set("force",me->query_maxforce()*2);
	me->set("food", me->max_food_capacity());
        me->set("water", me->max_water_capacity());
	me->set_temp("xiao_end",time());
	me->add("faith",-100);
        return 1;
}

int help(object me)
{
        string str;
        if( !me )  return 0;
        str = @STR

        法术名称：凤凰涅磐
        法术所属：登仙大法
        法术效果：瞬间将自身状态恢复为最佳状态
        	  冷却时间30秒
        	  神通·凤凰血脉能减少冷却时间
		  使后自身busy 3-7 秒
		  不恢复法力
        法术条件：
                  雪山弟子
        	  人物等级40级
                  法力500点，消耗500点
                  登仙大法400级
                  门忠100点，消耗100点
STR;
        me->start_more(str);
        return 1;
}
