using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;

namespace ArduinoInterface
{
    public partial class Form1 : Form
    {
        //string sensorval;

        public Form1()
        {
            InitializeComponent();
            serialPort1.PortName = "COM8";
            serialPort1.BaudRate = 9600;
            serialPort1.Open();
        }

        private void Form1_Load_1(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            serialPort1.Write("1");

            //labInfo.Text = "LED 켜짐";
            button1.Enabled = false;
            button2.Enabled = true;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            serialPort1.Write("0");

            //labInfo.Text = "LED 꺼짐";
            button1.Enabled = true;
            button2.Enabled = false;
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            //포트가 열려있나?
            if (true == serialPort1.IsOpen)
            {
                //포트를 닫는다.
                serialPort1.Close();
            }
        }
        
        
        // 130930 여기부터는 시리얼포트의 값을 richTextBox에 표시하려고 했지만 실패했음.
        /* 
        private void serialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            sensorval = serialPort1.ReadLine();
            this.Invoke(new EventHandler(richTextBox1_TextChanged));
        }

        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {
            richTextBox1.AppendText(sensorval);
            richTextBox1.ScrollToCaret();
        }
        
        /*
        void richTextBox1_TextChanged(object sender, EventArgs e)
        {
            int index = richTextBox1.GetFirstCharIndexOfCurrentLine();
            int line = richTextBox1.GetLineFromCharIndex(index) + 1;
            richTextBox1.Text = line.ToString();
        }*/        
    }
}
