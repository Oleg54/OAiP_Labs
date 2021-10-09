#include <iostream>
#include <random>

using namespace std;

const int SORTERS_COUNT = 7;




//класс для фиксирования времени работы части программы
class JobTimer
{
public:
	//начинает отсчет времени
	void BeginTimer()
	{
		_time = 0;
		//запоминает начальное количество тактов процессора
		_startPerfomanceCount = _Query_perf_counter();
	}

	//прекращает отсчет времени 
	void EndTimer()
	{
		//вычисляет количество тактов, сделанных за время выполнения программы, и делит его на 
		//количество тактов в секунду, получая время выполнения программы в секундах
		_time = (_Query_perf_counter() - _startPerfomanceCount) / (double)_Query_perf_frequency();
	}

	//возвращает вычисленное время
	double GetTime()
	{
		return _time;
	}

private:
	bool _timerIsBegin;
	double _time;

	long long _startPerfomanceCount;
};


//структура для хранения данных о сортировке массива (длина и время)
struct SortGraphPoint
{
public:
	int ArrayElementCount;
	double SortTime;
};

//структура, хранящая несколько измерений 
//скорости одного алгоритма на разных массивах
struct SortGraphData
{
public:
	string AlgorithmName;
	//массив измерений
	SortGraphPoint* points;
};






//класс, тестирующий алгоритмы
class SortingTester
{

public:
	
	//метод, производящий тестирование и возвращающий массив данных
	//производит измерение на массивах разнйо длины, 
	//pointCount -  количество измерений для каждого метода сортировки
	//arrayLengthMultiplier - множитель для уменьшения длины массива с каждой 
	//повторной итерацией
	SortGraphData* GetGraphs(int maxArrayLength, int pointCount, float arrayLengthMultiplier)
	{
		//инициализация
		SortGraphData* graphs = new SortGraphData[SORTERS_COUNT];

		//массив названий методов
		string sortNames[] = { "Пузырек", "Расческа", "Вставками", "Шелла", "Выбором", "Гномья", "Быстрая"};

		//добавление данных и метода сортировки в массив данных
		for (int i = 0; i < SORTERS_COUNT; i++)
		{
			graphs[i].AlgorithmName = sortNames[i];
			graphs[i].points = new SortGraphPoint[pointCount];
		}

		//измерение скоростей, tempArrayLength отвечает за длину массива,
		//с каждой итерацией дли на уменьшается
		for (int tempArrayLength = 0; tempArrayLength < pointCount; tempArrayLength++)
		{
			//вычисление текущей длины массива
			int currentArrayLength = maxArrayLength * pow(arrayLengthMultiplier, tempArrayLength);

			//генерация массива необходимой длины
			int* tempArray = GenerateArray(currentArrayLength);

			//методы сортировки возвращают время их работы
			//заполнение данных, запоминается длина сортируемого массива и время
			graphs[0].points[pointCount - 1 - tempArrayLength].ArrayElementCount = currentArrayLength;
			graphs[0].points[pointCount - 1 - tempArrayLength].SortTime = BubbleSort(tempArray, currentArrayLength);
			//это выполняется для каждого метода сортировки
			tempArray = GenerateArray(currentArrayLength);
			graphs[1].points[pointCount - 1 - tempArrayLength].ArrayElementCount = currentArrayLength;
			graphs[1].points[pointCount - 1 - tempArrayLength].SortTime = CombSort(tempArray, currentArrayLength);


			tempArray = GenerateArray(currentArrayLength);
			graphs[2].points[pointCount - 1 - tempArrayLength].ArrayElementCount = currentArrayLength;
			graphs[2].points[pointCount - 1 - tempArrayLength].SortTime = InsertSort(tempArray, currentArrayLength);


			tempArray = GenerateArray(currentArrayLength);
			graphs[3].points[pointCount - 1 - tempArrayLength].ArrayElementCount = currentArrayLength;
			graphs[3].points[pointCount - 1 - tempArrayLength].SortTime = ShellSort(tempArray, currentArrayLength);


			tempArray = GenerateArray(currentArrayLength);
			graphs[4].points[pointCount - 1 - tempArrayLength].ArrayElementCount = currentArrayLength;
			graphs[4].points[pointCount - 1 - tempArrayLength].SortTime = ChoiceSort(tempArray, currentArrayLength);


			tempArray = GenerateArray(currentArrayLength);
			graphs[5].points[pointCount - 1 - tempArrayLength].ArrayElementCount = currentArrayLength;
			graphs[5].points[pointCount - 1 - tempArrayLength].SortTime = GnomSort(tempArray, currentArrayLength);


			tempArray = GenerateArray(currentArrayLength);
			graphs[6].points[pointCount - 1 - tempArrayLength].ArrayElementCount = currentArrayLength;
			graphs[6].points[pointCount - 1 - tempArrayLength].SortTime = QuickSort(tempArray, 0, currentArrayLength - 1);
		}

		return graphs;
	}



private:

	JobTimer _jobTimer;


	//"Пузырек"
	double BubbleSort(int* arr, int arrayLength)
	{
		//начало отсчета
		_jobTimer.BeginTimer();

		for (int i = 0; i < arrayLength; i++)
		{
			for (int x = 1; x < arrayLength - i; x++)
			{
				if (arr[x - 1] > arr[x])
				{
					Swap(arr, x, x - 1);
				}
			}
		}
		//конец отсчета
		_jobTimer.EndTimer();
		//возвращение времени выполения
		return _jobTimer.GetTime();
		//в других методах аналогично
	}

	//"Расческа"
	double CombSort(int _array[], int _arrayLength)
	{
		_jobTimer.BeginTimer();

		float k = 1.247f;

		for (int step = _arrayLength - 1; step > 0; step /= k)
		{
			for (int x = 0; x < _arrayLength - step; x++)
			{
				if (_array[x] > _array[x + step])
				{
					Swap(_array, x, x + step);
				}
			}
		}
		_jobTimer.EndTimer();
		return _jobTimer.GetTime();
	}

	//"Вставками"
	double InsertSort(int _array[], int _arrayLength)
	{
		_jobTimer.BeginTimer();

		int i, j;
		int currentElement;
		for (i = 1; i < _arrayLength; i++)
		{
			for (j = i, currentElement = _array[i]; j > 0 && _array[j - 1] > currentElement; j--)
			{
				_array[j] = _array[j - 1];
			}
			_array[j] = currentElement;
		}
		_jobTimer.EndTimer();
		return _jobTimer.GetTime();
	}

	//"Шелла"
	double ShellSort(int _array[], int _arrayLength)
	{
		_jobTimer.BeginTimer();

		int i, j;
		int currentElement;
		int step;

		for (step = _arrayLength / 2; step > 0; step /= 2)
		{
			for (i = step; i < _arrayLength; i++)
			{
			currentElement = _array[i]; 
			for (j = i; j >= step; j -= step)
			{
				if (currentElement < _array[j - step]) _array[j] = _array[j - step];
				else break;
			}
			_array[j] = currentElement;
			}
		}

		_jobTimer.EndTimer();
		return _jobTimer.GetTime();
	}

	//"Выбором"
	double ChoiceSort(int _array[], int _arrayLength)
	{
		_jobTimer.BeginTimer();

		int i;
		int minElementIndex;
		for (i = 0; i < _arrayLength - 1; i++)
		{
			minElementIndex = i;
			for (int j = i + 1; j < _arrayLength; j++)
			{
				if (_array[j] < _array[minElementIndex]) minElementIndex = j;
			}
			Swap(_array, i, minElementIndex);
		}

		_jobTimer.EndTimer();
		return _jobTimer.GetTime();
	}

	//"Гномья"
	double GnomSort(int arr[], int arrayLength)
	{
		_jobTimer.BeginTimer();

		for (int i = 1, j = 2; i < arrayLength;)
		{
			if (arr[i - 1] > arr[i])
			{
				Swap(arr, i, i - 1);
				i--;
				if (i > 0) continue;
			}
			i = j++;
		}

		_jobTimer.EndTimer();
		return _jobTimer.GetTime();
	}

	//"Быстрая"
	double QuickSort(int* arr, int startIndex, int finalIndex)
	{
		//создание собственного экземпляра таймера
		//так как метод рекурсивный, при каждом вызове он обнуляет общий счетчик
		JobTimer jt;
		jt.BeginTimer();

		int pivot = arr[(startIndex + finalIndex) / 2];
		int l = startIndex;
		int r = finalIndex;
		while (l <= r)
		{
			while (arr[l] < pivot) l++;
			while (arr[r] > pivot) r--;
			if (l <= r)
			{
				Swap(arr, l, r);
				l++;
				r--;
			}
		}

		if (startIndex < r) QuickSort(arr, startIndex, r);
		if (l < finalIndex) QuickSort(arr, l, finalIndex);

		jt.EndTimer();
		return jt.GetTime();
	}


	//метод меняет два элемента массива с указанными индексами
	void Swap(int _array[], int _index1, int _index2)
	{

		int _temp = _array[_index1];
		_array[_index1] = _array[_index2];
		_array[_index2] = _temp;
	}

	//генерирует массив указанной длины со случайными числами
	int* GenerateArray(int requiredArrayLength)
	{
		int* outArray = new int[requiredArrayLength];
		//класс, генерирующий случайные числа
		random_device random;
		for (int i = 0; i < requiredArrayLength; i++) outArray[i] = random();
		return outArray;
	}
};






int main()
{
	//для вывода русских букв в консоль
	setlocale(LC_ALL, "Russian");

	SortingTester tester;

	//назначение параметров тестирования
	int pointCount = 6;
	float lengthMultiplier = 0.7f;

	SortGraphData* data = tester.GetGraphs(10000, pointCount, lengthMultiplier);

	//вывод результатов
	for (int i = 0; i < SORTERS_COUNT; i++)
	{
		cout << "Сортировка " << data[i].AlgorithmName << " отсортировала массив из:" << endl;
		for (int p = 0; p < pointCount; p++)
		{
			cout << data[i].points[p].ArrayElementCount << " элементов за " << data[i].points[p].SortTime << " секунд" << endl;
		}
		cout << "\n";
	}
}

