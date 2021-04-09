// ban.c

void create()
{
	seteuid(getuid());
}

int main(object me, string arg)
{
	string site;

	if (!arg)
		BAN_D->print();
	else if (sscanf(arg, "+ %s", site) == 1) {
		if (site[sizeof(site)-1] == '*' ||
		    site[sizeof(site)-1] == '?' ||
		    site[sizeof(site)-1] == '+')
			write("不能禁以 *, +, ? 结尾的地址。\n");
		else
			BAN_D->add(site);
		}
	else if (sscanf(arg, "- %s", site) == 1)
		BAN_D->remove(site);
	else write("指令格式：ban [+|- site]\n");

	return 1;
	
}

int help(object me)
{
	write(@HELP
指令格式：ban [+|- site]

当有人搞破坏时可以拒绝其相关IP的连线。
HELP
	);
	return 1;
}
