// drunk.c

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
	int limit;

//	limit = (me->query("con") + (int)me->query("max_force") / 50) * 2;

	// 10/13/98 mon adjusted drunk limit.
	// increased basic tolerance and reduced force effect.
// limit = me->query("kar")*6+(int)me->query("max_force")/50;
limit = me->query("per")*6+(int)me->query("max_force")/50;

	if( duration > limit
	&&	living(me) ) {
		me->unconcious();
		return 0;
	} else if( !living(me) ) {
		message("vision", me->name() + "打了个隔，不过依然烂醉如泥。\n",
			environment(me), me);
	} else if( duration > limit/5 ) {
		tell_object(me, "你觉得脑中昏昏沉沉，身子轻飘飘地，大概是醉了。\n");
		message("vision", me->name() + "摇头晃脑地站都站不稳，显然是喝醉了。\n",
			environment(me), me);
		me->receive_damage("sen", 10);
	} else if( duration > limit/10 ) {
		tell_object(me, "你觉得一阵酒意上冲，眼皮有些沉重了。\n");
		message("vision", me->name() + "脸上已经略显酒意了。\n",
			environment(me), me);
		me->receive_damage("sen", 3);
		//me->receive_healing("gin", 4);
		//me->receive_healing("kee", 4);
	}

	me->apply_condition("drunk", duration - 1);
	if( !duration ) return 0;
	return 1;
}
