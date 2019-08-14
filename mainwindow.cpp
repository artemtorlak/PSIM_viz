#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stages.h"
#include "memory.h"
#include "assert.h"
#include <QString>
#include <bitset>

using namespace std;

MainWindow::MainWindow(QWidget *parent, std::vector<uint32_t> insns, uint32_t* regs) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    stage_num = -1;
    ui->setupUi(this);

    PC = 0;
    PC_DISP = 0;
    check_J = 0;
    PC_R = 0;
    BP_EX = 0;
    BP_MEM = 0;
    local_PC = 0;
    branch = 0;
    counter = 0;
    q = 0;

    for(int i = 0; i < 100; i++)
        for(int j = 0; j < 35; j++)
            saved_value[i][j] = 0;

    instr_data_mem.set_insn(insns);
    instr_data_mem.print_memory();
    regfile.set_regfile(regs);

    QPixmap pm("/home/user1/PSIM_24april/11.jpg");
    ui -> picture -> setPixmap(pm);
    ui -> picture -> setScaledContents(true);
    ui -> PC_ -> setText(QString::number(PC));
    ui -> PC_DISP_ -> setText(QString::number(PC_DISP));
    ui -> PC_R_ -> setText(QString::number(PC_R));
    ui -> local_PC_ -> setText(QString::number(local_PC));
    ui -> branch_ -> setText(QString::number(branch));
    ui -> reverse_button ->setEnabled(false);
    //ui -> check_J_ -> setText(QString::number(check_J));
    connect(ui->my_button, SIGNAL(clicked()), this, SLOT(myclicked()));
    connect(ui -> reverse_button, SIGNAL(clicked()), this, SLOT(revers_button_click()));
}
void MainWindow::revers_button_click() {

    //assert(counter >= 0);

    ui -> insn -> setText(QString::number(saved_value[counter][30], 2));
    ui -> PC_ -> setText(QString::number(saved_value[counter][27]));
    ui -> PC_DISP_ -> setText(QString::number(saved_value[counter][28]));
    ui -> branch_ -> setText(QString::number(saved_value[counter][29]));

    ui -> RS1 -> setText(QString::number(saved_value[counter][0], 2));
    ui -> RS2 -> setText(QString::number(saved_value[counter][1], 2));
    ui -> RS1_val -> setText(QString::number(saved_value[counter][2], 2));
    ui -> RS2_val -> setText(QString::number(saved_value[counter][3],2));
    ui -> imm1 -> setText(QString::number(saved_value[counter][4], 2));
    ui -> imm2 -> setText(QString::number(saved_value[counter][5], 2));
    ui -> rd -> setText(QString::number(saved_value[counter][6], 2));
    ui -> local_PC_ -> setText(QString::number(saved_value[counter][7], 2));

    ui -> AluOp -> setText(QString::number(saved_value[counter][8], 2));
    ui -> mux_ex -> setText(QString::number(saved_value[counter][9], 2));
    ui -> ALU_resultl -> setText(QString::number(saved_value[counter][10], 2));
    ui -> conditionall -> setText(QString::number(saved_value[counter][11], 2));
    ui -> stop -> setText(QString::number(saved_value[counter][12], 2));
    ui -> RS1_val_execute -> setText(QString::number(saved_value[counter][13], 2));
    ui -> RS2_val_execute -> setText(QString::number(saved_value[counter][14], 2));
    ui -> RS1_val_2 -> setText(QString::number(saved_value[counter][15], 2));
    ui -> RS2_val_2 -> setText(QString::number(saved_value[counter][16], 2));
    ui -> PC_R_ -> setText(QString::number(saved_value[counter][17]));

    ui -> mux_mem -> setText(QString::number(saved_value[counter][18], 2));
    ui -> MEM_WE -> setText(QString::number(saved_value[counter][19], 2));
    ui -> mux_result -> setText(QString::number(saved_value[counter][20], 2));
    ui -> ALU_result_memory -> setText(QString::number(saved_value[counter][21], 2));
    ui -> RS1_val_memory -> setText(QString::number(saved_value[counter][22], 2));
    ui -> RD -> setText(QString::number(saved_value[counter][23], 2));

    ui -> WB_WE -> setText(QString::number(saved_value[counter][24], 2));
    ui -> WB_D -> setText(QString::number(saved_value[counter][25], 2));
    ui -> stop -> setText(QString::number(saved_value[counter][26], 2));

    counter--;
    ui -> clock -> setText(QString::number(counter));

    if(counter <= 0)
    {
        ui -> reverse_button ->setEnabled(false);
    }
    else
    {
        ui -> reverse_button ->setEnabled(true);
    }
}

//строк, столбцов
void MainWindow::myclicked() {
    std::cout << "clicked()" << std::endl;
    std::cout << PC << std::endl;
    std::cout << PC_DISP << std::endl;
    //execute_one_stage((stage_num++)%6);

    if(counter != q)
    {
        counter ++;
        ui -> clock -> setText(QString::number(counter));

        if(counter >=0)
        {
            ui -> reverse_button ->setEnabled(true);
        }

        ui -> insn -> setText(QString::number(saved_value[counter+1][30], 2));
        ui -> PC_ -> setText(QString::number(saved_value[counter+1][27]));
        ui -> PC_DISP_ -> setText(QString::number(saved_value[counter+1][28]));
        ui -> branch_ -> setText(QString::number(saved_value[counter+1][29]));

        ui -> RS1 -> setText(QString::number(saved_value[counter+1][0], 2));
        ui -> RS2 -> setText(QString::number(saved_value[counter+1][1], 2));
        ui -> RS1_val -> setText(QString::number(saved_value[counter+1][2], 2));
        ui -> RS2_val -> setText(QString::number(saved_value[counter+1][3],2));
        ui -> imm1 -> setText(QString::number(saved_value[counter+1][4], 2));
        ui -> imm2 -> setText(QString::number(saved_value[counter+1][5], 2));
        ui -> rd -> setText(QString::number(saved_value[counter+1][6], 2));
        ui -> local_PC_ -> setText(QString::number(saved_value[counter+1][7], 2));

        ui -> AluOp -> setText(QString::number(saved_value[counter+1][8], 2));
        ui -> mux_ex -> setText(QString::number(saved_value[counter+1][9], 2));
        ui -> ALU_resultl -> setText(QString::number(saved_value[counter+1][10], 2));
        ui -> conditionall -> setText(QString::number(saved_value[counter+1][11], 2));
        ui -> stop -> setText(QString::number(saved_value[counter+1][12], 2));
        ui -> RS1_val_execute -> setText(QString::number(saved_value[counter+1][13], 2));
        ui -> RS2_val_execute -> setText(QString::number(saved_value[counter+1][14], 2));
        ui -> RS1_val_2 -> setText(QString::number(saved_value[counter+1][15], 2));
        ui -> RS2_val_2 -> setText(QString::number(saved_value[counter+1][16], 2));
        ui -> PC_R_ -> setText(QString::number(saved_value[counter+1][17]));

        ui -> mux_mem -> setText(QString::number(saved_value[counter+1][18], 2));
        ui -> MEM_WE -> setText(QString::number(saved_value[counter+1][19], 2));
        ui -> mux_result -> setText(QString::number(saved_value[counter+1][20], 2));
        ui -> ALU_result_memory -> setText(QString::number(saved_value[counter+1][21], 2));
        ui -> RS1_val_memory -> setText(QString::number(saved_value[counter+1][22], 2));
        ui -> RD -> setText(QString::number(saved_value[counter+1][23], 2));

        ui -> WB_WE -> setText(QString::number(saved_value[counter+1][24], 2));
        ui -> WB_D -> setText(QString::number(saved_value[counter+1][25], 2));
        ui -> stop -> setText(QString::number(saved_value[counter+1][26], 2));

    }

    else
    {
        counter++;
        q++;
        bool fOK;

        ui -> clock -> setText(QString::number(counter));

        if(counter >=0)
        {
            ui -> reverse_button ->setEnabled(true);
        }

        for(int i = 0; i < 10; i++)
        {
            for(int j = 0; j < 35; j++)
                std::cout << saved_value[i][j] << " ";

            std::cout<<std::endl;
        }
        saved_value[counter][30] = (ui-> insn -> text()).toInt(&fOK, 2);
        saved_value[counter][27] = (ui-> PC_ -> text()).toInt();
        saved_value[counter][28] = (ui-> PC_DISP_ -> text()).toInt(&fOK, 2);
        saved_value[counter][29] = (ui-> branch_ -> text()).toInt(&fOK, 2);

        Fetch_reg_new fetch_tmp = fetch_stage(instr_data_mem, PC, PC_DISP, PC_R, local_PC, branch, check_J);
        fetch_tmp.print_reg();
        bool ok;
        QString hexString = (std::to_string(fetch_tmp.get_reg())).c_str();
        ui -> insn -> setText(QString("%1").arg(hexString.toULongLong(&ok, 16), 32, 2, QChar('0')));

            ui -> PC_ -> setText(QString::number(PC));
            ui -> PC_DISP_ -> setText(QString::number(PC_DISP));
            ui -> branch_ -> setText(QString::number(branch));

        saved_value[counter+1][30] = (ui-> insn -> text()).toInt(&fOK, 2);
        saved_value[counter+1][27] = (ui-> PC_ -> text()).toInt();
        saved_value[counter+1][28] = (ui-> PC_DISP_ -> text()).toInt(&fOK, 2);
        saved_value[counter+1][29] = (ui-> branch_ -> text()).toInt(&fOK, 2);

        std::cout << PC << std::endl;
        std::cout << "SAVED_VALUE[30] :" << (ui-> PC_ -> text()).toInt()<< std::endl;

        std::cout << (ui-> RS1 -> text()).toInt() << std::endl;
        saved_value[counter][0] = (ui-> RS1 -> text()).toInt(&fOK, 2);
        saved_value[counter][1] = (ui-> RS2 -> text()).toInt(&fOK, 2);
        saved_value[counter][2] = (ui-> RS1_val -> text()).toInt(&fOK, 2);
        saved_value[counter][3] = (ui-> RS2_val -> text()).toInt(&fOK, 2);
        saved_value[counter][4] = (ui-> imm1 -> text()).toInt(&fOK, 2);
        saved_value[counter][5] = (ui-> imm2 -> text()).toInt(&fOK, 2);
        saved_value[counter][6] = (ui-> rd -> text()).toInt(&fOK, 2);
        saved_value[counter][7] = (ui-> local_PC_ -> text()).toInt(&fOK, 2);


        Decode_reg decode_tmp = decode_stage(fetch_reg, regfile, HazardUnit);
        decode_tmp.print_reg();
        std::cout << "DECODE_REG:" << std::endl;
        ui -> RS1 -> setText(QString::number(decode_tmp.get_rs1(), 2));
        ui -> RS2 -> setText(QString::number(decode_tmp.get_rs2(), 2));
        ui -> RS1_val -> setText(QString::number(decode_tmp.get_rs1_val(), 2));
        ui -> RS2_val -> setText(QString::number(decode_tmp.get_rs2_val(),2));
        ui -> imm1 -> setText(QString::number(decode_tmp.get_imm1(), 2));
        ui -> imm2 -> setText(QString::number(decode_tmp.get_imm2(), 2));
        ui -> rd -> setText(QString::number(decode_tmp.get_rd(), 2));
        ui -> local_PC_ -> setText(QString::number(decode_tmp.get_local_PC(), 2));
    //8

        std::cout << (ui-> RS1 -> text()).toInt() << std::endl;
        saved_value[counter+1][0] = (ui-> RS1 -> text()).toInt(&fOK, 2);
        saved_value[counter+1][1] = (ui-> RS2 -> text()).toInt(&fOK, 2);
        saved_value[counter+1][2] = (ui-> RS1_val -> text()).toInt(&fOK, 2);
        saved_value[counter+1][3] = (ui-> RS2_val -> text()).toInt(&fOK, 2);
        saved_value[counter+1][4] = (ui-> imm1 -> text()).toInt(&fOK, 2);
        saved_value[counter+1][5] = (ui-> imm2 -> text()).toInt(&fOK, 2);
        saved_value[counter+1][6] = (ui-> rd -> text()).toInt(&fOK, 2);
        saved_value[counter+1][7] = (ui-> local_PC_ -> text()).toInt(&fOK, 2);


        saved_value[counter][8] = (ui-> AluOp -> text()).toInt(&fOK, 2);
        saved_value[counter][9] = (ui-> mux_ex -> text()).toInt(&fOK, 2);
        saved_value[counter][10] = (ui-> ALU_resultl -> text()).toInt(&fOK, 2);
        saved_value[counter][11] = (ui-> conditionall -> text()).toInt(&fOK, 2);
        saved_value[counter][12] = (ui-> stop -> text()).toInt(&fOK, 2);
        saved_value[counter][13] = (ui-> RS1_val_execute -> text()).toInt(&fOK, 2);
        saved_value[counter][14] = (ui-> RS2_val_execute -> text()).toInt(&fOK, 2);
        saved_value[counter][15] = (ui-> RS1_val_2 -> text()).toInt(&fOK, 2);
        saved_value[counter][16] = (ui-> RS2_val_2 -> text()).toInt(&fOK, 2);
        saved_value[counter][17] = (ui-> PC_R_ -> text()).toInt(&fOK, 2);

        Execute_reg execute_tmp = execute_stage(decode_reg, PC_DISP, PC_R, BP_EX, BP_MEM, local_PC, branch, HazardUnit, check_J);
        execute_tmp.print_reg();
        ui -> AluOp -> setText(QString::number(execute_tmp.get_CU_reg().AluOp, 2));
        ui -> mux_ex -> setText(QString::number(execute_tmp.get_CU_reg().mux_ex, 2));
        ui -> ALU_resultl -> setText(QString::number(execute_tmp.get_ALUresult(), 2));
        ui -> conditionall -> setText(QString::number(execute_tmp.get_CU_reg().conditional, 2));
        ui -> stop -> setText(QString::number(execute_tmp.get_CU_reg().stop, 2));
        ui -> RS1_val_execute -> setText(QString::number(decode_reg.get_rs1_val(), 2));
        ui -> RS2_val_execute -> setText(QString::number(decode_reg.get_rs2_val(), 2));
        ui -> RS1_val_2 -> setText(QString::number(execute_tmp.get_rs2_val(), 2));
        ui -> RS2_val_2 -> setText(QString::number(decode_reg.get_rs1_val(), 2));
        ui -> PC_R_ -> setText(QString::number(PC_R));
    //10
        saved_value[counter+1][8] = (ui-> AluOp -> text()).toInt(&fOK, 2);
        saved_value[counter+1][9] = (ui-> mux_ex -> text()).toInt(&fOK, 2);
        saved_value[counter+1][10] = (ui-> ALU_resultl -> text()).toInt(&fOK, 2);
        saved_value[counter+1][11] = (ui-> conditionall -> text()).toInt(&fOK, 2);
        saved_value[counter+1][12] = (ui-> stop -> text()).toInt(&fOK, 2);
        saved_value[counter+1][13] = (ui-> RS1_val_execute -> text()).toInt(&fOK, 2);
        saved_value[counter+1][14] = (ui-> RS2_val_execute -> text()).toInt(&fOK, 2);
        saved_value[counter+1][15] = (ui-> RS1_val_2 -> text()).toInt(&fOK, 2);
        saved_value[counter+1][16] = (ui-> RS2_val_2 -> text()).toInt(&fOK, 2);
        saved_value[counter+1][17] = (ui-> PC_R_ -> text()).toInt(&fOK, 2);

        saved_value[counter][18] = (ui-> mux_mem -> text()).toInt(&fOK, 2);
        saved_value[counter][19] = (ui-> MEM_WE -> text()).toInt(&fOK, 2);
        saved_value[counter][20] = (ui-> mux_result -> text()).toInt(&fOK, 2);
        saved_value[counter][21] = (ui-> ALU_result_memory -> text()).toInt(&fOK, 2);
        saved_value[counter][22] = (ui-> RS1_val_memory -> text()).toInt(&fOK, 2);
        saved_value[counter][23] = (ui-> RD -> text()).toInt(&fOK, 2);

        Memory_reg memory_tmp = memory_stage(execute_reg, instr_data_mem, BP_EX, branch, HazardUnit);
        memory_tmp.print_reg();
        ui -> mux_mem -> setText(QString::number(memory_tmp.get_CU_reg().mux_mem, 2));
        ui -> MEM_WE -> setText(QString::number(memory_tmp.get_CU_reg().MEM_WE, 2));
        ui -> mux_result -> setText(QString::number(memory_tmp.get_mux_res(), 2));
        ui -> ALU_result_memory -> setText(QString::number(execute_reg.get_ALUresult(), 2));
        ui -> RS1_val_memory -> setText(QString::number(execute_reg.get_rs2_val(), 2));
        ui -> RD -> setText(QString::number(memory_tmp.get_rd(), 2));
    //6
        saved_value[counter+1][18] = (ui-> mux_mem -> text()).toInt(&fOK, 2);
        saved_value[counter+1][19] = (ui-> MEM_WE -> text()).toInt(&fOK, 2);
        saved_value[counter+1][20] = (ui-> mux_result -> text()).toInt(&fOK, 2);
        saved_value[counter+1][21] = (ui-> ALU_result_memory -> text()).toInt(&fOK, 2);
        saved_value[counter+1][22] = (ui-> RS1_val_memory -> text()).toInt(&fOK, 2);
        saved_value[counter+1][23] = (ui-> RD -> text()).toInt(&fOK, 2);

        saved_value[counter][24] = (ui-> WB_WE -> text()).toInt(&fOK, 2);
        saved_value[counter][25] = (ui-> WB_D -> text()).toInt(&fOK, 2);
        saved_value[counter][26] = (ui-> stop -> text()).toInt(&fOK, 2);

        write_back_stage(memory_reg, regfile, BP_MEM, branch, HazardUnit);
        ui -> WB_WE -> setText(QString::number(memory_tmp.get_CU_reg().WB_WE, 2));
        ui -> WB_D -> setText(QString::number(memory_tmp.get_rd(), 2));
        ui -> stop -> setText(QString::number(memory_tmp.get_CU_reg().stop, 2));
    //3
        saved_value[counter+1][24] = (ui-> WB_WE -> text()).toInt(&fOK, 2);
        saved_value[counter+1][25] = (ui-> WB_D -> text()).toInt(&fOK, 2);
        saved_value[counter+1][26] = (ui-> stop -> text()).toInt(&fOK, 2);

        HazardUnit.Run(fetch_tmp, decode_tmp, execute_tmp, memory_tmp);
        fetch_reg = execute_tmp.GetFlush() ? Fetch_reg_new() : fetch_tmp;
        decode_reg = execute_tmp.GetFlush() ? Decode_reg() : decode_tmp;
        execute_reg = execute_tmp;
        memory_reg = memory_tmp;
    //sum = 27
    //    ui -> PC_ -> setText(QString::number(PC));
    //    ui -> PC_DISP_ -> setText(QString::number(PC_DISP));
    //    ui -> branch_ -> setText(QString::number(branch));
        //ui -> check_J_ -> setText(QString::number(check_J));
     };
}

MainWindow::~MainWindow()
{
    delete ui;
}


uint32_t MainWindow::get_PC() {
    return PC;
}

uint32_t MainWindow::get_PC_DISP() {
    return PC_DISP;
}
