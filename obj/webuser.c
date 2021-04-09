// webuser.c
// neva 为xserver 双头龙模式制造该命令
// 2003年2月7日


inherit F_CLEAN_UP;


int main( object me )
{
	if( me->is_busy() )
		return notify_fail("你的上一个动作还未完成.\n");

	if( me->is_fighting() )
		return notify_fail("你正在战斗中.\n");


	if( me->query("position") == "zmuduser") {
		me->set("position", "webuser");
		message_vision("$N 设定使用网页浏览器进行游戏。\n", me);
	} else if( me->query("position") == "webuser") {
		return notify_fail("你已经设定为使用网页浏览器连接进行游戏模式了。\n");
	} 
	return 1;
}

int help( object me)
{
	write(@HELP
指令格式: webuser
该指令让使用网页浏览器进行游戏的玩家可以看到正常的显示。

相关指令: zmuduser
HELP
	);
        return 1;
}
