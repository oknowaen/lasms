namespace IDEAssembler
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void assembleButton_Click(object sender, EventArgs e)
        {
            string[] lines = { 
                textBox1.Text, 
                textBox2.Text, 
                textBox3.Text, 
                textBox4.Text, 
                textBox5.Text, 
                textBox6.Text, 
                textBox7.Text, 
                textBox8.Text, 
                textBox8.Text, 
                textBox9.Text, 
                textBox10.Text, 
                textBox11.Text, 
                textBox12.Text, 
                textBox13.Text, 
                textBox14.Text 
            };

            string outfilepath = textBox15.Text;

            byte[] bytes = new byte[28];
            int index = 0;

            foreach (string line in lines)
            {
                if (line == "") continue;

                if (index != 0) index++;

                byte ins = FindInstruction(line.Split(' ')[0]);
                byte param = Convert.ToByte(Convert.ToInt32(line.Split(' ')[1]));

                bytes[index] = ins;
                index++;
                bytes[index] = param;
            }

            File.WriteAllBytes(outfilepath, bytes);

            MessageBox.Show("Assembly Complete.", "Alert", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private byte FindInstruction(string line)
        {
            if (line == "LDA") return 0xA1;
            else if (line == "LDX") return 0xA2;
            else if (line == "LDY") return 0xA3;
            else if (line == "PTS") return 0x8B;
            else if (line == "ADD") return 0xE4;
            else if (line == "INC") return 0x5A;
            else if (line == "END") return 0xFF;

            return 0x00;
        }
    }
}