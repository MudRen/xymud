// inherit object: knower.c
// 消息灵通人士继承此对象

#include <ansi.h>

int is_knower() { return 1; }

// 接收打听消息
mixed accept_ask(object ob, string topic)
{
        return QUEST_D->generate_information(this_object(), ob, topic);
}
