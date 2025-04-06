# hadoop basic level 정의

## Hadoop - Basic
The Hadoop open-source software framework is widely used for reliable, and scalable distributed computing on a cluster of machines.

This competency area includes understanding Single node cluster in a standalone mode, in pseudo-distributed mode, running shell commands to interface with HDFS, performing parallel processing tasks, among others. 

Key Competencies:

1. Single node cluster in a standalone mode - Install Java environment, download the Hadoop jar and run Hadoop as a standalone process. Applicable for Operations, Developer.
2. Single node cluster in pseudo-distributed mode - Configure SSH, format, and start the name node and data node daemons, configure and run the YARN process. Applicable for Operations, Developer.
3. Monitor cluster and jobs - Monitor name nodes and data nodes using the name node web interface, monitor resource usage using the ResourceManager. Applicable for Administration, Developer.
4. Run shell commands to interface with HDFS - Run basic list and view commands on HDFS, run commands to store and read data from HDFS, copy files to and from Hadoop. Applicable for Operations, Developer.
5. Perform parallel processing tasks using MapReduce - Set up the Mapper, Reducer classes to process data stored in HDFS, derive from the right base classes, set up the basic configuration to run MapReduce jobs. Applicable for Developer.
6. Schedule and manage tasks with YARN - Use the FIFO scheduler, capacity scheduler, and fair scheduler, configure task queues and submit MapReduce tasks to a specific queue. Applicable for Administration, Developer.
7. Set up and configure a Hadoop cluster on a cloud platform - Configure a simple Hadoop cluster using either Amazon EMR, Azure HDInsight, or Google Cloud DataProc. Applicable for Administration, Developer.
8. Run MapReduce jobs on Hadoop on a cloud platform - Run MapReduce jobs on Amazon EMR, Azure HDInsight, or Google Cloud DataProc. Configure bucket storage rather than HDFS storage on the cloud. Applicable for Operations, Developer.


# 1. MapReduce
큰 데이터를 가공하고 집계할 떄, 포크-조인 디바이드-앤-컨커를 수행하는 개념.
디바이드 한 데이터들을 병렬로 처리하자는 개념 ㄷㄷ -> 다른 머신에서도 가능

![Image](https://github.com/user-attachments/assets/23e1d641-b471-48d7-8d6b-8ec93e1287ed)

여기서 Mapper과 Reducer를 주로 커스텀 한다.

### 그럼 하둡은 뭐함?
입력을 분할하거나, Map을 수행할 JVM을 띄우고 중간 파일을 정리하고, Shuffle 하는 등의 행위는 Hadoop이 알아서 처리해준다.
Shuffle & Reduce 시에도 같은 Key의 단어가 같은 곳으로 모이게 전부 처리해 준다. (원한다면 어떤 Key를 어떤 Reduce로 보낼 지도 Partiioner를 바꿔 구현해볼 수 있다.)

### 진행 과정
결국 데이터로 무엇을 할지가 중요한데, <br>
**원하는 결과를 얻기 위해 Mapper에서 가공하고, Reducer에서 처리한다고 생각하면 될 듯** <br> <br>

1. 파일(데이터) HDFS에 업로드
2. Job 제출
3. **YARN ResourceManager**가
  - 입력 블록 = InputSplit 매핑
  - 데이터가 있는 DataNode에 Map 컨테이너 기동
4. **Map 태스크**
  - 사용자 Mapper 로직 실행. (key, value) → 로컬 디스크에 파티션·정렬
  - Reducer에서 처리하기 위해, 원본 데이터를 가공
5. Shuffle 단계
  - 같은 파티션 ID를 가진 중간 파일들을 해당 Reduce 컨테이너로 전송
  - 같이 처리되야 하는 데이터들 같은 Reduce로..
5. **Reduce 태스크**
  - 사용자 Reducer 로직으로 최종 집계
  - 결과를 HDFS(OutputPath)에 저장

4. Job 완료 → 상태·카운터를 HistoryServer/UI에서 조회

# 2. :star: MapReduce 구현해보기
## 2.1 단어 갯수 세기 (예시 그림에 나온)
```java
public class WordCounter {

    public static class TokenizerMapper extends Mapper<Object, Text, Text, IntWritable> {
        private final static IntWritable one = new IntWritable(1);
        private final Text word = new Text();

        public void map(Object key, Text value, Context context) throws IOException, InterruptedException {
            StringTokenizer itr = new StringTokenizer(value.toString());
            while (itr.hasMoreTokens()) {
                word.set(itr.nextToken());
                context.write(word, one);
            }
        }
    }

    public static class IntSumReducer extends Reducer<Text, IntWritable, Text, IntWritable> {
        private final IntWritable result = new IntWritable();

        public void reduce(Text key, Iterable<IntWritable> values, Context context) throws IOException, InterruptedException {
            int sum = 0;
            for (IntWritable val : values) {
                sum += val.get();
            }
            result.set(sum);
            context.write(key, result);
        }
    }

    public static void main(String[] args) throws Exception {
        Configuration conf = new Configuration();
        Job job = Job.getInstance(conf, "wordCounter");
        job.setJarByClass(WordCounter.class);

        // 위에서 만든 Mapper랑 Reducer 적용
        job.setMapperClass(TokenizerMapper.class);
        job.setCombinerClass(IntSumReducer.class);
        job.setReducerClass(IntSumReducer.class);

        job.setOutputKeyClass(Text.class);
        job.setOutputValueClass(IntWritable.class);

        if (args.length < 2) {
            args = new String[] {
                "/user/binary-ho/input",
                "/user/binary-ho/output"
            };
        }

        FileInputFormat.addInputPath(job, new Path(args[0]));
        FileOutputFormat.setOutputPath(job, new Path(args[1]));

        System.exit(job.waitForCompletion(true) ? 0 : 1);
    }
}
```

## 2.2 Group By로 부서별 Salary 합치기
```java
public class GroupBySum {

    public static class CsvMapper extends Mapper<Object, Text, Text, DoubleWritable> {
        private final Text dept = new Text();
        private final DoubleWritable salary = new DoubleWritable();

        @Override
        protected void map(Object key, Text value, Context ctx) throws IOException, InterruptedException {
            String line = value.toString();
            if (line.startsWith("id,")) {
                // 첫 번째 줄은 헤더이므로 무시
                return;
            }

            String[] parts = line.split(",", -1);        // id,name,dept,salary
            if (parts.length < 4) {
                // 잘못된 형식의 데이터 무시
                return;
            }

            dept.set(parts[2]);                          // dept 컬럼
            salary.set(Double.parseDouble(parts[3]));    // salary 컬럼
            ctx.write(dept, salary);                     // (dept, salary) emit
        }
    }

    public static class SumReducer extends Reducer<Text, DoubleWritable, Text, DoubleWritable> {
        private final DoubleWritable result = new DoubleWritable();

        @Override
        protected void reduce(Text key, Iterable<DoubleWritable> vals, Context ctx)
            throws IOException, InterruptedException {
            double sum = 0;
            for (DoubleWritable v : vals) sum += v.get();
            result.set(sum);
            ctx.write(key, result);                      // (dept, 총급여)
        }
    }

    public static void main(String[] args) throws Exception {
        if (args.length != 2) {
            System.err.println("Usage: DeptSalarySum <input> <output>");
            System.exit(-1);
        }

        Configuration conf = new Configuration();
        Job job = Job.getInstance(conf, "Dept Salary Sum");
        job.setJarByClass(GroupBySum.class);

        job.setMapperClass(CsvMapper.class);
        job.setCombinerClass(SumReducer.class);
        job.setReducerClass(SumReducer.class);

        job.setOutputKeyClass(Text.class);
        job.setOutputValueClass(DoubleWritable.class);

        FileInputFormat.addInputPath(job, new Path(args[0]));
        FileOutputFormat.setOutputPath(job, new Path(args[1]));

        System.exit(job.waitForCompletion(true) ? 0 : 1);
    }
}
```

## 2.3 친구 명수 세기 예시
input이 아래와 같이 주어질 때, 친구가 몇명인지 세어 보여주기
```md
- Input
Joe Sue
Sue Phi
Phi Joe
Phi Alice

- Output
{"key":"Alice","value":"1"}
{"key":"Joe","value":"2"}
{"key":"Phi","value":"3"}
{"key":"Sue","value":"2"}
```

python 코드 - mapper와 reducer에 집중
```py
from collections import OrderedDict
class MapReduce:
    def __init__(self):
        self.intermediate = OrderedDict()
        self.result = []
   

    def emitIntermediate(self, key, value):
   	self.intermediate.setdefault(key, [])       
        self.intermediate[key].append(value)

    def emit(self, value):
        self.result.append(value) 

    def execute(self, data, mapper, reducer):
        for record in data:
            mapper(record)

        for key in self.intermediate:
            reducer(key, self.intermediate[key])

        self.result.sort()
        for item in self.result:
            print "{\"key\":\""+item[0]+"\",\"value\":\"" + str(item[1]) + "\"}"

mapReducer = MapReduce()

def mapper(record):
    split = record.split()
    mapReducer.emitIntermediate(split[0], split[1])
    mapReducer.emitIntermediate(split[1], split[0])

def reducer(key, list_of_values):
    mapReducer.emit([key, len(list_of_values)])
    
```


# 3. 설치 및 접속
1. [이거 참고하면 거의 문제 없음](https://sseozytank.tistory.com/78)

## HDFS 명령어 실습
### 3.1 디렉터리 생성 및 파일 업로드
```sh
# HDFS에 /user/binary-ho 디렉터리 생성
hdfs dfs -mkdir -p /user/binary-ho

# 테스트용 로컬 파일 생성
echo "Hello Hadoop!" > hello.txt

# 파일을 HDFS에 업로드
hdfs dfs -put hello.txt /user/binary-ho/

# HDFS에서 확인
hdfs dfs -ls /user/binary-ho
```

### 3.2 hdfs에서 파일 읽기, 로컬로 옮기기
```sh
# 파일 내용 보기
hdfs dfs -cat /user/binary-ho/hello.txt

# 파일을 로컬로 복사해오기
hdfs dfs -copyToLocal /user/binary-ho/hello.txt ./downloaded.txt

# 로컬에서 확인
cat downloaded.txt
```
### 3.3 기타 명령어
```sh
`-mkdir`: 디렉토리 생성
`-put`:	로컬 → HDFS 업로드
`-get` / `-copyToLocal`: HDFS → 로컬 복사
`-cat`: HDFS 파일 내용 출력
`-ls`: 목록 보기
`-du`: -h 용량 보기
`-rm`, `-rm -r`: 파일/디렉터리 삭제
`-mv`: 파일 이동/이름 변경
`-test`: -e <경로> 파일 존재 확인
```


## 내 ubuntu WSL에서 시작할 때
```sh
# ssh 시작 (225 에러 뜨면)
sudo service ssh start

# Permission denied: Rcmd Type이 rsh로 되어 있는 경우 (pdsh -q -w localhost)
export PDSH_RCMD_TYPE=ssh
source ~/.bashrc

# 시작
~/hadoop/sbin/start-all.sh

# 멈추기
~/hadoop/sbin/stop-all.sh
```


```sh
# 시작 예시
mkdir ./build/wordcounter

javac -classpath $(hadoop classpath) -d ./build/wordcounter ./WordCounter.java

jar -cvf ~/wordcounter.jar -C ./build/wordcounter .

hadoop jar ~/wordcounter.jar WordCounter \
  /user/binary-ho/input /user/binary-ho/output

# 출력 보기
hdfs dfs -ls /user/binary-ho/output

hdfs dfs -cat /user/binary-ho/output/part-r-00000
```
