#include "Administrator.h"

void menu_admin(map <string, Account>& accounts)
{
		vector <string> menu = { "МЕНЮ АДМИНИСТРАТОРА", 
														 "1 - Просмотр учетных записей", 
														 "2 - Редактирование учетной записи", 
														 "3 - Добавление учетной записи", 
														 "4 - Удаление учетной записи",
														 "5 - Просмотр всех цветов",
														 "6 - Редактирование цветов",
														 "7 - Заявка на закупку цветов",
														 "8 - Списание цветов",
														 "9 - Статистика дохода",
														 "10 - Выход"};

		int choice = menu_helper(menu);

		switch (choice)
		{
		case 1:
				break;
		default:
				return;
		}
}
