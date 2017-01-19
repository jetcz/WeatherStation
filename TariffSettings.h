struct TariffDayInterval
{
	int on, off;

}; typedef struct TariffDaySettings TariffDaySettings;

struct TariffDaySettings
{
	TariffDayInterval intervals[3];

}; typedef struct TariffDaySettings TariffDaySettings;

/// <summary>
/// Tarrif settings for low and high, for each of week day there are 3 intervals, different intervals are on weekend
/// </summary>
struct Tariff
{
	TariffDaySettings setting[7];
	Tariff()
	{
		//workdays
		for (int i = 0; i < 5; i++)
		{
			TariffDaySettings ts;

			TariffDayInterval ti;
			ti.on = (13 * 60) + 3;
			ti.off = 15 * 60;

			ts.intervals[0] = ti;

			TariffDayInterval ti2;
			ti2.on = (19 * 60) + 3;
			ti2.off = 24 * 60;

			ts.intervals[1] = ti2;


			TariffDayInterval ti3;
			ti3.on = 0;
			ti3.off = (1 * 60) + 5;

			ts.intervals[2] = ti3;

			setting[i] = ts;
		}

		//weekend
		for (int i = 5; i < 7; i++)
		{
			TariffDaySettings ts;

			TariffDayInterval ti;
			ti.on = 4 * 60;
			ti.off = (10 * 60) + 5;

			ts.intervals[0] = ti;

			TariffDayInterval ti2;
			ti2.on = 12 * 60;
			ti2.off = (14 * 60) + 5;

			ts.intervals[1] = ti2;

			TariffDayInterval ti3;
			ti3.on = -1;
			ti3.off = -1;

			ts.intervals[2] = ti3;

			setting[i] = ts;
		}
	}

}; typedef struct TariffDaySettings TariffDaySettings;
