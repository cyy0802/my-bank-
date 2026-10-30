#include<stdio.h>
#include<string.h>

#define max_accounts 10000

#define data_file "D:\\bank.txt"

struct Account
{
	int id;				//账户			
	char name[4];		//名字	
	char password[7];	//密码 
	double balance;		//余额 
	int state;			//状态 
};

struct Account accounts[max_accounts];

int account_count = 0;

int i = 0;

void load_data(void);
void save_data(void);
int find_account(int id);
void open_account(void);
void enter(void);
void leave(void);
void query_balance(void);
void close_account(void);
void all_account(void);
void menu(void);

//菜单
void menu(void)
{
	printf("------------------------------\n");
	printf("欢迎使用银行管理系统！\n");
	printf("请输入服务前对应的标号以服务\n");
	printf("1. 开户\n");
	printf("2. 存款\n");
	printf("3. 取款\n");
	printf("4. 查询余额\n");
	printf("5. 销户\n");
	printf("6. 显示所有账户\n");
	printf("0. 退出\n");
	printf("请选择:\n");
}
// 加载数据过程 

void load_data(void)
{
	FILE* fp = fopen(data_file, "r");
	if (fp == NULL)
	{
		printf("请创建账户\n");
		return;
	}
	account_count = 0;
	while (account_count < max_accounts && fscanf(
		fp, "%d %s %s %lf %d",
		&accounts[account_count].id,
		&accounts[account_count].name,
		&accounts[account_count].password,
		&accounts[account_count].balance,
		&accounts[account_count].state
	) == 5)
		{
            account_count++;
        }
	fclose(fp);
}

//保存数据
void save_data(void)
{
	FILE* fp = fopen(data_file, "w");
	if (fp == NULL)
	{
		printf("数据保存失败\n");
		return;
	}

	for (i = 0;i < account_count;i++)
	{
		fprintf(fp, "%d %s %s %lf %d",
			accounts[i].id,
			accounts[i].name,
			accounts[i].password,
			accounts[i].balance,
			accounts[i].state);

	}
	fclose(fp);
	printf("数据保存成功\n");
}
//查找账户
int find_account(int id)
{
	for (i = 0;i < account_count;i++)
	{
		if (accounts[i].id == id && accounts[i].state == 1)
		{
			return i;
		}
	}
	return -1;
}
// 开户
void open_account(void)
{
	if (account_count > max_accounts)
	{
		printf("超过上限，停止开户\n");
		return;
	}
    else
    {
	struct Account account1;
	printf("请输入姓名:\n");
	scanf("%3s", account1.name);
	printf("请输入密码:\n");
	scanf("%6s", account1.password);
	int max_id = 0;
	for (i = 0;i < account_count;i++)
	{
		if (max_id < accounts[i].id)
		{
			max_id = accounts[i].id;
		}
	}
    // 100 5 200
	account1.id = max_id + 1;
	account1.balance = 0.0;
	account1.state = 1;
	accounts[account_count] = account1;
	account_count++;
	save_data();
	printf("开户成功，账号为%d\n", account1.id);
    }
}

//存款 
void enter(void)
{
	int id;
	double amount;
	printf("请输入账号\n");
	scanf("%d", &id);
	int id_yes = find_account(id);
	if (id_yes < 0)
	{
		printf("账号无效\n");
		return;
	}
	else
	{
		printf("请输入存款金额\n");
		scanf("%lf", &amount);
	}
	if (amount < 0)
	{
		printf("余额输入错误\n");
		return;
	}
	accounts[id_yes].balance += amount;
	save_data();
	printf("存款成功，当前余额为%.2f\n", accounts[id_yes].balance);
}
//取款
void leave(void)
{
	int id;
	double amount;
	printf("请输入账号\n");
	scanf("%d", &id);
	int id_yes = find_account(id);
	if (id_yes < 0)
	{
		printf("账号无效\n");
		return;
	}
	else
	{
		printf("请输入取款金额\n");
		scanf("%lf", &amount);
	}
	if (amount <= 0)
	{
		printf("请输入正确金额\n");
		return;
	}
	if (accounts[id_yes].balance < amount)
	{
		printf("余额不足!\n");
		return;
	}
	else
	{
		accounts[id_yes].balance -= amount;
	}
	save_data();
	printf("取款成功，当前余额为%lf元\n", accounts[id_yes].balance);
}
//余额查询
void query_balance(void)
{
	int id;
	char password[7];
	printf("请输入账号\n");
	scanf("%d", &id);
	int id_yes = find_account(id);
	if (id_yes < 0)
	{
		printf("该账户不存在\n");
		return;
	}
	printf("请输入密码\n");
	scanf("%6s", password);
	if (strcmp(password, accounts[id_yes].password) != 0)
	{
		printf("密码错误！\n");
		return;
	}
	printf("账号:%d\n", accounts[id_yes].id);
	printf("姓名:%s\n", accounts[id_yes].name);
	printf("余额:%.2f\n", accounts[id_yes].balance);
}
//销户
void close_account(void)
{
	int id;
	char password[7];
	printf("请输入需要销号的账户\n");
	scanf("%d", &id);
	int id_yes = find_account(id);
	if (id_yes < 0)
	{
		printf("该账号不存在\n");
		return;
	}
	printf("请输入密码\n");
	scanf("%6s", password);
	if (strcmp(password, accounts[id_yes].password) != 0) {
		printf("密码错误！\n");
		return;
	}
	if (accounts[id_yes].balance != 0)
	{
		printf("账户仍有余额 %.2f元请先取款清空\n", accounts[id_yes].balance);
		return;
	}
	accounts[id_yes].state = 0;
	save_data();
	printf("销户成功。\n");
}
//展示所有账户
void all_account(void)
{
	printf("----------------------------------------\n");
	if (account_count == 0)
	{

		printf("无账户\n");
		return;
	}
	for (int i = 0;i < account_count;i++)
	{
		if (accounts[i].state == 1)
		{
			printf("账户:%d\n姓名:%s\n余额:%.2f\n", accounts[i].id, accounts[i].name, accounts[i].balance);
			printf("----------------------------------------\n");
		}
	}
}
// 主函数 
int main()
{
	load_data();
	int input ;
	while (1)
	{
		menu();
		if (scanf("%d", &input) == 0)
		{
			printf("请输入正确数字\n");
			while (getchar() != '\n');
			continue;
		}
		switch (input)
		{
		
		case 1: open_account();    break;
		case 2: enter();   	 break;
		case 3: leave();       	 break;
		case 4: query_balance();   break;
		case 5: close_account();   break;
        case 6: all_account();        break;
        case 0:
			save_data();
			printf("再见！\n");
			return 0;
		}
	}
	return 0;
}

