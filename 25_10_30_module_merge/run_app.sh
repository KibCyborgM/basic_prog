CPP_FILES="io.cpp merge.cpp merge_sort.cpp main.cpp"
APP=merge_sort

if [ -f $APP ]; then rm $APP
fi

g++ $CPP_FILES -o $APP

./$APP