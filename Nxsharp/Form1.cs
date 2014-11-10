using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Net;
using System.Net.NetworkInformation;
using global::System.Windows.Forms;
using System.Threading;
using System.IO;
using Microsoft.Win32;
//using System.Windows.Forms.Layout;

namespace gui
{
    public partial class Form1:Form
    {
        StringBuilder outSb = new StringBuilder();
        public Form1()
        {
            Control.CheckForIllegalCrossThreadCalls = false;
            InitializeComponent();
            this.textBox1.Text = Cfg.username;
            this.textBox2.Text = Cfg.password;
            this.comboBox1.Text = Cfg.device;
            this.checkBox1.Checked = Cfg.store;
            this.checkBox2.Checked = Cfg.auto;

            foreach (string adapter in NetworkInterfaceAvaliable.adapters_dict.Keys)
            {
                //this.comboBox1.Items.Add(adapter.Name + "\n" + adapter.Id + "\n" + adapter.Description);
                this.comboBox1.Items.Add(adapter);
            }
            if (NetworkInterfaceAvaliable.adapters_dict.ContainsKey(Cfg.device))
            {
                this.comboBox1.Text = Cfg.device;
            }
            else
            {
                this.comboBox1.Text = this.comboBox1.Items[0].ToString();
            }
            if (Cfg.auto)
            {
                button1_Click(button1, new EventArgs());
            }
            //this.comboBox1.Text = "1";
            //this.comboBox1.Items = NetworkInterfaceAvaliable.adapters_avaliable.Description;
            SystemEvents.PowerModeChanged += new PowerModeChangedEventHandler(OnPowerModeChanged);
            
        }
        System.Timers.Timer t = new System.Timers.Timer(50); //此为日志框的刷新计时器
        private void button3_Click(object sender, EventArgs e)
        {
            //if(this.Height == 375)
            //{
            //    panel1.Visible = false;
            //    this.Height = 200;
            //}
            //else if(this.Height ==200)
            //{
            //    panel1.Visible = true;
            //    this.Height = 375;

            //}
            //NetworkInterfaceAvaliable.RefreshDHCP(NetworkInterfaceAvaliable.adapters_dict[comboBox1.Text]);
            Form2 f2 = new Form2();
            f2.ShowDialog();            
        }

        private void notifyIcon1_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            this.Show();
            this.ShowInTaskbar = true;
            this.WindowState = FormWindowState.Normal;
            this.BringToFront();
        }

        public void button1_Click(object sender, EventArgs e)
        {
            Cfg.username = textBox1.Text;
            Cfg.password = textBox2.Text;
            Cfg.device = comboBox1.Text;
            Cfg.store = checkBox1.Checked;
            Cfg.auto = checkBox2.Checked;
            if(checkBox1.Checked)
            {
                Cfg.Commit();
            }
            else
            {
                Cfg.username = null;
                Cfg.password = null;
                Cfg.store = false;
                Cfg.auto = false;
                Cfg.Commit();
            }
            RefComm.start_auth_thread(Cfg.username, Cfg.password, "\\Device\\NPF_" + NetworkInterfaceAvaliable.adapters_dict[comboBox1.Text]);
            //textBox1.Enabled = false;
            //textBox2.Enabled = false;
            //checkBox1.Enabled = false;
            //checkBox2.Enabled = false;
            button1.Enabled = false;
            button2.Enabled = true;
            panel1.Enabled = false;
            textBox3.Text = "";
            t.Elapsed += new System.Timers.ElapsedEventHandler(refreshText);
            t.AutoReset = true;
            t.Enabled = true;
        }

        private void button5_Click(object sender, EventArgs e)
        {
            this.Height = 175;
            panel2.Visible = false;
        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {

        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            if(checkBox1.Checked)
            {
                checkBox2.Enabled = true;
            }
            else
            {
                checkBox2.Enabled = false;
                checkBox2.Checked = false;
            }
        }

        private void checkBox2_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            RefComm.stop_auth_thread();
            panel1.Enabled = true;
            button1.Enabled = true;
            button2.Enabled = false;
            textBox3.AppendText("\r\n已登出");
            t.Enabled = false;
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            Cfg.device = comboBox1.Text;
        }
        private void refreshText(object source, System.Timers.ElapsedEventArgs e)
        {
            string tmp = RefComm.read_log();



            if (tmp.Length != 0)
            {
                if (textBox3.Text.Length > 32700)
                {
                    textBox3.Text = "";
                    textBox3.ScrollToCaret();
                    //textBox3.AppendText("");
                }
                textBox3.ScrollToCaret();//自动滚屏
                //textBox3.Focus();
                //textBox3.SelectionStart=textBox3.Text.Length;
                //textBox3.SelectionLength = 0;
                
                textBox3.AppendText(tmp);
                textBox3.ScrollToCaret();
            }
            //自动更新IP
            if (tmp.Contains("Success"))
            {
                //textBox3.ScrollToCaret();//自动滚屏
                //textBox3.Focus();
                //textBox3.SelectionStart = textBox3.Text.Length;
                //textBox3.SelectionLength = 0;
                //textBox3.ScrollToCaret();
                NetworkInterfaceAvaliable.RefreshDHCP(NetworkInterfaceAvaliable.adapters_dict[comboBox1.Text]);
                textBox3.AppendText("IP Refreshed.\r\n");
                textBox3.ScrollToCaret();//自动滚屏
            }

        }

        private void Form1_Deactivate(object sender, EventArgs e)
        {
            if (this.WindowState == FormWindowState.Minimized)
            {
                this.ShowInTaskbar = false;
                this.Hide();
            }
        }

        private void textBox3_TextChanged(object sender, EventArgs e)
        {

        }

        private void Form1_Activated(object sender, EventArgs e)
        {
            textBox3.ScrollToCaret();//自动滚屏到最下
            //textBox3.Focus();
            //textBox3.SelectionStart = textBox3.Text.Length;
            //textBox3.SelectionLength = 0;
            //textBox3.ScrollToCaret();
        }
        private void OnPowerModeChanged(object sender, PowerModeChangedEventArgs e)
        {
            if (button1.Enabled == false && button2.Enabled == true) //判断是否点击登录
            {
                switch (e.Mode)
                {
                    //系统挂起
                    case PowerModes.Suspend:
                        RefComm.stop_auth_thread();
                        textBox3.AppendText("\r\n已登出");
                        break;
                    //系统恢复
                    case PowerModes.Resume:
                        RefComm.start_auth_thread(Cfg.username, Cfg.password, "\\Device\\NPF_" + NetworkInterfaceAvaliable.adapters_dict[comboBox1.Text]);
                        break;
                }
            }

        }
    }
}
