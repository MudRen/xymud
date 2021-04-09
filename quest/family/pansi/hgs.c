inherit ROOM;

void create ()
{
	set ("short", "花果山顶");
	set ("long", @LONG
这里是花果山顶的一块平地。一道瀑布从这里飞流直下，
泻入下方一眼深潭，当真是：“一派白虹起，千寻雪浪飞”。
    瀑布边上隐约有一块大石头，相传为天地灵气所化。不
知是谁在上面刻了一首诗：

　　　　混沌未分天地乱，茫茫渺渺无人见。
　　　　自从盘古破鸿蒙，开辟从兹清浊辨。

LONG);
  	set("outdoors", 1);
	setup();
}

mixed valid_move(object me)
{
	object dog,erlang,qingxia,zixia;
	if( !userp(me) || !clonep(this_object())
	 || me!=query("owner") )
		return 0;
	if( !me->query_temp("pendding/fc_visite")
    	 || me->is_knowing("puti_panlong")
    	 || me->query_temp("pendding/fc_visite_pansi")
    	 || me->query_temp("pendding/fc_visite_pansikill")
    	 || !me->query_temp("pendding/fc_pansiask") )
    	 	return 0;
    	if( time()>=me->query("family/guanli_pansi_fail")+3600 ) 
    		me->set("family/guanli_pansi_fail",time());
    	qingxia = me->query_temp("pendding/fc_qingxia");
    	if( qingxia )
    		destruct(qingxia);
    	zixia = me->query_temp("pendding/fc_zixia");
	if( zixia )
		destruct(zixia);
	erlang = me->query_temp("pendding/fc_erlang");
	if( erlang )
	{
		dog = erlang->query_temp("invoker");
		if( dog )
			destruct(dog);
		destruct(erlang);
	}
	if( clonep(this_object()) )
		REMOVE_D->add_room(this_object(),5);
	return "你离开了副本地图。\n";	
}