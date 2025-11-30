# include<iostream>
# include<vector>
# include<string>
using namespace std; 

/***************************************************
string    Bfr    буферная строка для копир.
vector    File    итоговый файл
          Kmd     список команд
int       Ksr     курсор (текущий номер строки)
          Sdv     Сдвиг up/down после нажатия Shift
          ShPos   Позиция нажатого Shift 
***************************************************/
int main()
{
  size_t Ksr = 0, ShPos; /* Ставим "курсор" на первую строку*/
  size_t Sdv = 0; /* Величина сдвига при зажатом Shift*/
  size_t i;
  string Str;
  vector<string> Bfr; 
  vector<string> File;
  vector<string> Kmd;
  bool NSh = false; /* Нажат ли Shift? */
  while (getline(cin, Str) && !Str.empty()) /* Запись в файл */
    File.push_back(Str);

  File.push_back(""); 

  while (getline(cin, Str)) /* Запись команд */
    Kmd.push_back(Str);   

  for (size_t i = 0;  i < Kmd.size();  i++) 
  { 
    /* ==================== КНОПКА SHIFT ========================== */
    if (Kmd[i] == "Shift") /* Нажали SHIFT */
    {
      NSh = true; 
      ShPos = Ksr;
      Sdv = 0; 
      continue;
    }
    /* ==================== КНОПКА DOWN ========================== */
    if (Kmd[i] == "Down") 
    {
      if (!NSh) /* Shift не нажат */
        if (Ksr < (File.size() - 1))
          Ksr++;
      else /* Shift нажат */
      {
        if (Ksr < (File.size() - 1))
        {
          Ksr++;
          Sdv++;
        }
        else if (Ksr == (File.size() - 1)) /*Shift + Down на посл.стр.*/
          Sdv++; 
      }
      continue;
    }
    /* =================== КНОПКА UP =========================== */
    if (Kmd[i] == "Up") 
    {
      if (!NSh)
        if (Ksr > 0)
          Ksr--; 
      else
      {
        if (Ksr > 0)
        {
          Ksr--;
          Sdv--;
        }
      }
      continue;
    }
    /* ==================== КНОПКА CTRL_X ========================== */
    if (Kmd[i] == "Ctrl+X") 
    { 
      if (!NSh)
      {
        if (!File[Ksr].empty())
        {
          Bfr.clear(); 
          Bfr.push_back(File[Ksr]); 
          File.erase(File.begin() + Ksr);
        }
      }
      else
      {
        if (!File.empty())
        {
          Bfr.clear();
          if (Sdv >= 0) 
          {
            for (i = ShPos;  i < ShPos + Sdv;  i++)
              Bfr.push_back(File[i]);

            File.erase(File.begin() + ShPos, File.begin() + ShPos + Sdv);
          }
          else if (Sdv < 0)
          {
            for (i = ShPos - Sdv;  i < ShPos;  i++)
              Bfr.push_back(File[i]);
            
            File.erase(File.begin() + ShPos - Sdv, File.begin() + ShPos);
          }
        }
        NSh = false;
        ShPos = 0;
        Sdv = 0; 
      }
      continue;
    }
    /* ==================== КНОПКА CTRL_V ========================== */
    if (Kmd[i] == "Ctrl+V") 
    {
      // Shift не нажат
      // Shift нажат
        // Sdv >= 0
        // Sdv < 0
      // обнуления NSh, ShPos, Sdv; 
      continue;
    }
  }

  for (size_t i = 0;  i < File.size();  i++)
    cout << File[i] << endl; 
}


