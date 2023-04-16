package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	filePath := "/proc/mydev"
	file, err := os.OpenFile(filePath, os.O_RDWR, 0666)
	if err != nil {
		fmt.Println("文件打開失敗", err)
	}
	//及時關閉file句柄
	defer file.Close()
	reader := bufio.NewReader(file)
	p := make([]byte, 100)
	reader.Read(p)
	fmt.Println(string(p))

	fmt.Print("write some message:")
	stdin_reader := bufio.NewReader(os.Stdin)
	text, _ := stdin_reader.ReadString('\n')
	fmt.Print(text)
	d1 := []byte(text)
	err = os.WriteFile("/proc/mydev", d1, 0666)
	if err != nil {
		fmt.Println("write err")
	}

}
