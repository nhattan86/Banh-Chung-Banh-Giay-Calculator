// main.cpp
#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QMessageBox>
#include <cmath>

#define PI 3.1415926535

class WeatherCalculator : public QMainWindow {
private:
    QLineEdit* nInput;
    QLineEdit* dcInput;
    QLineEdit* dgInput;
    QLineEdit* ldInput;
    QComboBox* weatherCombo;
    QLabel* resultLabel;
    
    // Original variables
    int n, dc, dg, ld;
    double nbg, nd;
    int nbc, bc, bg, tld;

    int amicable(int n, int ld) {
        int s1 = 0;
        int s2 = 0;

        for (int j = 1; j <= n / 2; j++) {
            if (n % j == 0)
                s1 += j;
        }

        for (int j = 1; j <= ld / 2; j++) {
            if (ld % j == 0)
                s2 += j;
        }

        return (s1 == ld && s2 == n) ? 1 : 0;
    }

    void case_wind() {
        nbc = dc * dc;
        nbg = (dg * dg * PI) / 4;
        bc = n / nbc;
        nd = n - bc * nbc;
        bg = nd / nbg;
        nd = nd - bg * nbg;
        int max = bc;

        tld = bc + bg;

        if (tld > ld) {
            if (bc > ld) {
                bc = ld;
                bg = 0;
                nd = n - bc * nbc;
            } else {
                bc = max;
                bg = ld - bc;
                nd = n - bc * nbc - bg * nbg;
            }
        }
    }

    void case_rain() {
        int temp, bct, bgt;
        float ndbc, ndbg;
        nbc = dc * dc;
        nbg = (dg * dg * PI) / 4;
        nd = n;

        if (n >= 0) {
            bc = nd / nbc;
            nd = nd - bc * nbc;
            bg = nd / nbg;
            nd = nd - bg * nbg;
        }

        temp = bc + bg;
        temp = (temp > ld) ? ld : temp;

        if (temp % 2 == 0) {
            temp = temp / 2;
        } else {
            temp = (temp + 1) / 1.5;
        }

        bc = temp;
        bg = temp;
        nd = n - bc * nbc - bg * nbg;

        bct = nd / nbc;
        bgt = nd / nbg;

        ndbc = nd - (bc + bct) * nbc - bg * nbg;
        ndbg = nd - (bg + bgt) * nbg - bc * nbc;

        if (ndbc < ndbg) {
            bc = bc + bct;
        } else {
            bg = bg + bgt;
        }
        nd = n - bc * nbc - bg * nbg;

        while (nd < 0) {
            bc = bc - 1;
            bg = bg - 1;
            nd = n - bc * nbc - bg * nbg;
        }
    }

    void case_fog() {
        bc = dc;
        bg = dg;
        nd = n;
    }

    void case_cloud() {
        if (amicable(n, ld) == 1) {
            bc = 0;
            bg = 0;
            nd = n;
            return;
        }

        nbc = dc * dc;
        nbg = (dg * dg * PI) / 4;
        bg = n / nbg;
        nd = n - bg * nbg;
        bc = nd / nbc;
        nd = nd - bc * nbc;
        int max = bg;

        tld = bc + bg;

        if (tld > ld) {
            if (bg > ld) {
                bg = ld;
                bc = 0;
                nd = n - bg * nbg;
            } else {
                bg = max;
                bc = ld - bg;
                nd = n - bc * nbc - bg * nbg;
            }
        }
    }

    void case_sun() {
        int g = dc % 6;
        int h = ld % 5;
        float nt;
        int ldm;

        // Calculate nt and ldm based on g and h values
        if (g == 0) {
            if (h == 0) { nt = n + ((n * 5) / 100); ldm = ld - 5; }
            else if (h == 1) { nt = n + ((n * 20) / 100); ldm = ld - 20; }
            else if (h == 2) { nt = n + ((n * 15) / 100); ldm = ld - 15; }
            else if (h == 3) { nt = n + ((n * 12) / 100); ldm = ld - 12; }
            else { nt = n + ((n * 10) / 100); ldm = ld - 10; }
        }
        // ... (similar calculations for other g values)
        
        int ws = (dc + dg) % 3;
        
        if (ws == 0) { // rain
            n = nt;
            ld = ldm;
            case_rain();
        } else if (ws == 1) { // wind
            n = nt;
            ld = ldm;
            case_wind();
        } else { // cloud
            n = nt;
            ld = ldm;
            case_cloud();
        }
    }

public:
    WeatherCalculator(QWidget* parent = nullptr) : QMainWindow(parent) {
        setWindowTitle("Weather Calculator");
        setupUI();
    }

private:
    void setupUI() {
        QWidget* centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);
        
        QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
        
        // Create input fields
        QGridLayout* inputLayout = new QGridLayout();
        
        inputLayout->addWidget(new QLabel("N:"), 0, 0);
        nInput = new QLineEdit();
        inputLayout->addWidget(nInput, 0, 1);
        
        inputLayout->addWidget(new QLabel("DC:"), 1, 0);
        dcInput = new QLineEdit();
        inputLayout->addWidget(dcInput, 1, 1);
        
        inputLayout->addWidget(new QLabel("DG:"), 2, 0);
        dgInput = new QLineEdit();
        inputLayout->addWidget(dgInput, 2, 1);
        
        inputLayout->addWidget(new QLabel("LD:"), 3, 0);
        ldInput = new QLineEdit();
        inputLayout->addWidget(ldInput, 3, 1);
        
        inputLayout->addWidget(new QLabel("Weather:"), 4, 0);
        weatherCombo = new QComboBox();
        weatherCombo->addItems({"Rain", "Sun", "Cloud", "Fog", "Wind"});
        inputLayout->addWidget(weatherCombo, 4, 1);
        
        mainLayout->addLayout(inputLayout);
        
        // Create calculate button
        QPushButton* calculateBtn = new QPushButton("Calculate");
        connect(calculateBtn, &QPushButton::clicked, this, &WeatherCalculator::calculate);
        mainLayout->addWidget(calculateBtn);
        
        // Create result label
        resultLabel = new QLabel();
        resultLabel->setAlignment(Qt::AlignCenter);
        mainLayout->addWidget(resultLabel);
    }

    void calculate() {
        // Get input values
        bool ok;
        n = nInput->text().toInt(&ok);
        if (!ok) { showError("Invalid N value"); return; }
        
        dc = dcInput->text().toInt(&ok);
        if (!ok) { showError("Invalid DC value"); return; }
        
        dg = dgInput->text().toInt(&ok);
        if (!ok) { showError("Invalid DG value"); return; }
        
        ld = ldInput->text().toInt(&ok);
        if (!ok) { showError("Invalid LD value"); return; }
        
        // Validate input
        if (n > 1000 || ld < 1 || ld > 300) {
            bc = -1;
            bg = -1;
            showResult();
            return;
        }
        
        // Process based on weather
        QString weather = weatherCombo->currentText();
        if (weather == "Wind") {
            case_wind();
        } else if (weather == "Rain") {
            case_rain();
        } else if (weather == "Sun") {
            case_sun();
        } else if (weather == "Fog") {
            case_fog();
        } else { // Cloud
            case_cloud();
        }
        
        showResult();
    }

    void showResult() {
        if ((bc + bg) < 0) {
            resultLabel->setText(QString("Result: -1 -1 %1").arg(n));
        } else {
            resultLabel->setText(QString("Result: %1 %2 %.3f").arg(bc).arg(bg).arg(nd));
        }
    }

    void showError(const QString& message) {
        QMessageBox::warning(this, "Error", message);
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    WeatherCalculator calculator;
    calculator.show();
    return app.exec();
}