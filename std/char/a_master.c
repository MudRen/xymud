// a_master.c 宗师类师傅

#include <dbase.h>
#include <login.h>
#include <ansi.h>

int is_a_master()
{
	return 1;
}

int prevent_learn(object me, string skill)
{
	int betrayer;
	if( !me->is_apprentice_of(this_object())
        &&      (int)this_object()->query_skill(skill, 1) <= (int)me->query_skill(skill, 1) * 2 ) {
		command("hmm");
		command("pat " + me->query("id"));
		command("say 虽然你是我门下的弟子，可是并非我的嫡传弟子 ....");
		command("say 我只能教你这些粗浅的本门功夫，其他的还是去找你师父学吧。");
		return 1;
	}

	return 0;
}
