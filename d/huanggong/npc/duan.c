#include <ansi.h>
inherit NPC;

void create()
{
set_name("段志玄",({"duan zhixuan","duan"}));
set("gender","男性");
set("title","褒国公");
set("long",@LONG
高祖在太原时的旧部，首义功臣。参加李唐历次重要战役，以勇武著名。
太宗皇帝兄弟相争时，拒绝建成、元吉的拉拢，忠于太宗，并参加了玄武
门之变。其人治军严谨，太宗评价为“周亚夫无以加焉”。位列凌烟阁二十
四功臣之十。
LONG);
set("job","关");
set("age",65);
set("per",24);
setup();
carry_object("/d/obj/armor/jinjia.c")->wear();
}

string query_check_msg()
{
return "顺风耳告诉你：段志玄身有当今天子御赐的法宝，无法查出他的底细。\n";
}
