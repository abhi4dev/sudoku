#include <stdio.h>
#include <string.h>
#include <stdbool.h>

enum num {
ONE   = 0x1 << 0,
TWO   = 0x1 << 1,
THREE = 0x1 << 2,
FOUR  = 0x1 << 3,
FIVE  = 0x1 << 4,
SIX   = 0x1 << 5,
SEVEN = 0x1 << 6,
EIGHT = 0x1 << 7,
NINE  = 0x1 << 8,
LAST  = 0x1 << 9
};

unsigned int su[9][9] = {0};
unsigned int so[9][9] = {0};

void rowAlgo (unsigned int r, unsigned int c, unsigned int e);
void colAlgo (unsigned int r, unsigned int c, unsigned int e);
void boxAlgo (unsigned int r, unsigned int c, unsigned int e);

bool rowCheck (unsigned int r, unsigned int c, unsigned int e);
bool colCheck (unsigned int r, unsigned int c, unsigned int e);
bool boxCheck (unsigned int r, unsigned int c, unsigned int e);

void initTable (void)
{
  unsigned int ent = 0;

  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      ent = su[i][j];

      if (ent == 0)
      {
        su[i][j] = 0x1FF;
      }
    }
  }
}

unsigned int validNum (unsigned int e)
{
  switch (e)
  {
    case(ONE):
      return 1;
    case(TWO):
      return 2;
    case(THREE):
      return 3;
    case(FOUR):
      return 4;
    case(FIVE):
      return 5;
    case(SIX):
      return 6;
    case(SEVEN):
      return 7;
    case(EIGHT):
      return 8;
    case(NINE):
      return 9;
    default:
      return 0;
  }
  return 0;
}

void printTable (bool fin)
{
  unsigned int e = 0;

  printf ("\n-------------------------------------\n");
  for (int i = 0; i < 9 ; i++)
  {
    printf ("|");
    for (int j = 0; j < 9; j++)
    {
      if (fin == true)
      {
        e = so[i][j];
        if (e != 0)
        {
          printf (" %u |", e);
        }
        else
        {
          printf ("   |");
        }
      }
      else
      {
        e = su[i][j];
        if (e != 0)
        {
          printf (" %X |", e);
        }
        else
        {
          printf ("   |");
        }
      }
    }
    printf ("\n-------------------------------------\n");
  }
  return;
}

typedef struct counter
{
  unsigned short cnt;
  unsigned short r;
  unsigned short c;
} counter_t;

void singleNumPossRow (void)
{
  unsigned int i = 0, ent = 0;
  unsigned int r = 0, c = 0;
  counter_t cntr[9];

  for (r = 0; r < 9; r++)
  {
    memset (cntr, 0, sizeof(cntr));

    for (c = 0; c < 9; c++)
    {
      so[r][c] = validNum (su[r][c]);
      if (so[r][c] != 0)
      {
        continue;
      }
      else
      {
        for (i = 0; i < 9; i++)
        {
          if (su[r][c] & (0x1 << (i)))
          {
            cntr[i].cnt++;
            if (cntr[i].cnt == 1)
            {
              cntr[i].c = c;
            }
          }
        }
      }
    }

    for (i = 0; i < 9; i++)
    {
      if (cntr[i].cnt == 1)
      {
        c = cntr[i].c;

        ent = (0x1 << i);

        if ((true == rowCheck (r, c, ent)) ||
            (true == colCheck (r, c, ent)) ||
            (true == boxCheck (r, c, ent)))
        {
          continue;
        }

        su[r][c] = ent;
        so[r][c] = validNum (ent);
        if (so[r][c] != 0)
        {
          rowAlgo (r, c, ent);
          colAlgo (r, c, ent);
          boxAlgo (r, c, ent);
        }
      }
    }
  }
  return;
}

void singleNumPossCol (void)
{
  unsigned int i = 0, ent = 0;
  unsigned int r = 0, c = 0;
  counter_t cntr[9];

  for (c = 0; c < 9; c++)
  {
    memset (cntr, 0, sizeof(cntr));

    for (r = 0; r < 9; r++)
    {
      so[r][c] = validNum (su[r][c]);
      if (so[r][c] != 0)
      {
        continue;
      }
      else
      {
        for (i = 0; i < 9; i++)
        {
          if (su[r][c] & (0x1 << (i)))
          {
            cntr[i].cnt++;
            if (cntr[i].cnt == 1)
            {
              cntr[i].r = r;
            }
          }
        }
      }
    }

    for (i = 0; i < 9; i++)
    {
      if (cntr[i].cnt == 1)
      {
        r = cntr[i].r;

        ent = (0x1 << i);

        if ((true == rowCheck (r, c, ent)) ||
            (true == colCheck (r, c, ent)) ||
            (true == boxCheck (r, c, ent)))
        {
          continue;
        }

        su[r][c] = ent;
        so[r][c] = validNum (ent);
        if (so[r][c] != 0)
        {
          rowAlgo (r, c, ent);
          colAlgo (r, c, ent);
          boxAlgo (r, c, ent);
        }
      }
    }
  }
  return;
}

void singleNumPossBox (void)
{
  unsigned int i = 0, ent = 0;
  unsigned int br = 0, bc = 0;
  unsigned int r = 0, c = 0;
  unsigned int fr = 0, fc = 0;
  counter_t cntr[9];

  for (br = 0; br < 3; br++)
  {
    for (bc = 0; bc < 3; bc++)
    {
      memset (cntr, 0, sizeof(cntr));

      for (r = 0; r < 3; r++)
      {
        for (c = 0; c < 3; c++)
        {
          fr = (3*br) + r;
          fc = (3*bc) + c;
          so[fr][fc] = validNum (su[fr][fc]);
          if (so[fr][fc] != 0)
          {
            continue;
          }
          else
          {
            for (i = 0; i < 9; i++)
            {
              if ((su[fr][fc]) & (0x1 << (i)))
              {
                cntr[i].cnt++;
                if (cntr[i].cnt == 1)
                {
                  cntr[i].r = fr;
                  cntr[i].c = fc;
                }
              }
            }
          }
        }
      }

      for (i = 0; i < 9; i++)
      {
        if (cntr[i].cnt == 1)
        {
          r = cntr[i].r;
          c = cntr[i].c;

          ent = (0x1 << i);

          if ((true == rowCheck (r, c, ent)) ||
              (true == colCheck (r, c, ent)) ||
              (true == boxCheck (r, c, ent)))
          {
            continue;
          }

          su[r][c] = ent;
          so[r][c] = validNum (ent);
          if (so[r][c] != 0)
          {
            rowAlgo (r, c, ent);
            colAlgo (r, c, ent);
            boxAlgo (r, c, ent);
          }
        }
      }
    }
  }
  return;
}


bool rowCheck (unsigned int r, unsigned int c, unsigned int e)
{
  unsigned int ci = 0;
  unsigned int ent = 0;

  for (ci = 0; ci < 9; ci++)
  {
    ent = su[r][ci];
    so[r][ci] = validNum (ent);
    if ((so[r][ci] != 0) &&
        (ent == e))
    {
      return true;
    }
  }
  return false;
}

bool colCheck (unsigned int r, unsigned int c, unsigned int e)
{
  unsigned int ri = 0;
  unsigned int ent = 0;

  for (ri = 0; ri < 9; ri++)
  {
    ent = su[ri][c];
    so[ri][c] = validNum (ent);
    if ((so[ri][c] != 0) &&
        (ent == e))
    {
      return true;
    }
  }
  return false;
}

bool boxCheck (unsigned int r, unsigned int c, unsigned int e)
{
  unsigned int ri = r/3;
  unsigned int ci = c/3;
  unsigned int rs = ri*3;
  unsigned int cs = ci*3;
  unsigned int rm = rs+3;
  unsigned int cm = cs+3;
  unsigned int ent = 0;

  for (rs = ri*3; rs < rm; rs++)
  {
    for (cs = ci*3; cs < cm; cs++)
    {
      ent = su[rs][cs];
      so[rs][cs] = validNum (ent);
      if ((so[rs][cs] != 0) &&
          (ent == e))
      {
        return true;
      }
    }
  }
  return false;
}

void rowAlgo (unsigned int r, unsigned int c, unsigned int e)
{
  unsigned int ci = 0;
  unsigned int ent = 0;

  for (ci = 0; ci < 9; ci++)
  {
    ent = su[r][ci];
    so[r][ci] = validNum (ent);
    if (so[r][ci] != 0)
    {
      /* do nothing */
    }
    else
    {
      su[r][ci] &= ~e;
      ent = su[r][ci];
      so[r][ci] = validNum (ent);
      if (so[r][ci] != 0)
      {
        rowAlgo (r, ci, ent);
        colAlgo (r, ci, ent);
        boxAlgo (r, ci, ent);
      }
    }
  }
  return;
}

void colAlgo (unsigned int r, unsigned int c, unsigned int e)
{
  unsigned int ri = 0;
  unsigned int ent = 0;

  for (ri = 0; ri < 9; ri++)
  {
    ent = su[ri][c];
    so[ri][c] = validNum (ent);
    if (so[ri][c] != 0)
    {
      /* do nothing */
    }
    else
    {
      su[ri][c] &= ~e;
      ent = su[ri][c];
      so[ri][c] = validNum (ent);
      if (so[ri][c] != 0)
      {
        rowAlgo (ri, c, ent);
        colAlgo (ri, c, ent);
        boxAlgo (ri, c, ent);
      }
    }
  }
  return;
}

void boxAlgo (unsigned int r, unsigned int c, unsigned int e)
{
  unsigned int ri = r/3;
  unsigned int ci = c/3;
  unsigned int rs = ri*3;
  unsigned int cs = ci*3;
  unsigned int rm = rs+3;
  unsigned int cm = cs+3;
  unsigned int ent = 0;

  for (rs = ri*3; rs < rm; rs++)
  {
    for (cs = ci*3; cs < cm; cs++)
    {
      ent = su[rs][cs];
      so[rs][cs] = validNum (ent);
      if (so[rs][cs] != 0)
      {
        /* do nothing */
      }
      else
      {
        su[rs][cs] &= ~e;
        ent = su[rs][cs];
        so[rs][cs] = validNum (ent);
        if (so[rs][cs] != 0)
        {
          rowAlgo (rs, cs, ent);
          colAlgo (rs, cs, ent);
          boxAlgo (rs, cs, ent);
        }
      }
    }
  }
  return;
}

int main (void)
{
  unsigned int i = 0;
  unsigned int r = 0, c = 0;
  unsigned int ent = 0;
  char e[82];

  printf ("\ninput the table as series of numbers in row order. Use '0' for blank spaces.");

  printf ("\nEntries : ");
  scanf ("%s", e);

  for (i = 0; i < 81; i++)
  {
    r = i/9;
    c = i%9;

    ent = (unsigned int)(e[i] - '0');
    so[r][c] = ent;
    if (ent == 0)
    {
      su[r][c] = 0x1FF;
    }
    else
    {
      su[r][c] = 0x1 << (ent - 1);
    }

    if (ent > 9)
    {
      printf ("\n Invalid input\n");
      return 0;
    }
  }

  printf ("\n Input Table is : ");
  printTable (true);

  for (r = 0; r < 9; r++)
  {
    for (c = 0; c < 9; c++)
    {
      ent = su[r][c];
      so[r][c] = validNum (ent);
      if (so[r][c] != 0)
      {
        rowAlgo (r, c, ent);
        colAlgo (r, c, ent);
        boxAlgo (r, c, ent);
      }
    }
  }
  printTable (true);

for (i = 0; i < 3; i++)
{
  singleNumPossRow ();
  singleNumPossCol ();
  singleNumPossBox ();

  printTable (true);
}
  return 0;
}
