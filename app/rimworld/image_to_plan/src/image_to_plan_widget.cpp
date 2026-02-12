/*
 * MIT License
 *
 * Copyright (c) 2024 Sergei Cherevichko
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "image_to_plan_widget.h"

#include <QFileDialog>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QPixmap>
#include <QPushButton>
#include <QToolButton>
#include <QVBoxLayout>

#include <format>
#include <fstream>

namespace checo::rimworld
{

ImageToPlanWidget::ImageToPlanWidget(QWidget *parent, Qt::WindowFlags flags)
    : QWidget(parent, flags)
{
    // Global layout
    auto *layoutMain = new QVBoxLayout(this);
    setLayout(layoutMain);

    // Input image file
    auto *layoutImage = new QHBoxLayout();
    layoutMain->addLayout(layoutImage);

    m_EdtImagePath = new QLineEdit(this);
    layoutImage->addWidget(m_EdtImagePath);

    auto *btnSelectBmp = new QToolButton(this);
    btnSelectBmp->setText("...");
    connect(btnSelectBmp, &QToolButton::clicked, this, &ImageToPlanWidget::selectImage);
    layoutImage->addWidget(btnSelectBmp);

    // Output plan file
    auto *layoutPlan = new QHBoxLayout();
    layoutMain->addLayout(layoutPlan);

    m_EdtPlanPath = new QLineEdit(this);
    layoutPlan->addWidget(m_EdtPlanPath);

    auto *btnSelectPlan = new QToolButton(this);
    btnSelectPlan->setText("...");
    connect(btnSelectPlan, &QToolButton::clicked, this, &ImageToPlanWidget::selectPlan);
    layoutPlan->addWidget(btnSelectPlan);

    // Convert button
    auto *btnConvert = new QPushButton(tr("Convert"), this);
    connect(btnConvert, &QPushButton::clicked, this, &ImageToPlanWidget::convert);
    layoutMain->addWidget(btnConvert);
}

ImageToPlanWidget::~ImageToPlanWidget() = default;

void ImageToPlanWidget::selectImage()
{
    m_EdtImagePath->setText(QFileDialog::getOpenFileName(this, tr("Select input image file")));
}

void ImageToPlanWidget::selectPlan()
{
    m_EdtPlanPath->setText(QFileDialog::getSaveFileName(this, tr("Select output plan file")));
}

void ImageToPlanWidget::convert()
{
    static constexpr const char *PLAN_HEADER = R"(<?xml version="1.0" encoding="utf-8"?>
<savedPlanInfo>
	<planInfo>
		<Name>{}</Name>
		<Created>0</Created>
		<PlanLayout>
			<cells>
)";
    static constexpr const char *PLAN_FOOTER = R"(</cells>
		</PlanLayout>
	</planInfo>
</savedPlanInfo>
)";
    static constexpr const char *FMT_PLAN_PIXEL = R"(<li>
    <position>({}, {})</position>
    <designation>PlanWall</designation>
    <color>Structure_White</color>
</li>
)";

    // Load BMP
    QImage img = QPixmap(m_EdtImagePath->text()).toImage();

    // Open output plan file
    std::ofstream outPlan(m_EdtPlanPath->text().toStdString());

    // Write output plan header
    outPlan << std::format(PLAN_HEADER, QFileInfo(m_EdtPlanPath->text()).baseName().toStdString());

    // Convert each black pixel of the BMP into text file record
    const int imgHeight = img.height();
    for (int row = 0; row < imgHeight; ++row)
    {
        for (int col = 0; col < img.width(); ++col)
        {
            if (img.pixelColor(col, row) == Qt::black)
            {
                outPlan << std::format(FMT_PLAN_PIXEL, col, imgHeight - row - 1);
            }
        }
    }

    // Write output plan footer
    outPlan << PLAN_FOOTER;

    // Display notification on conversion finished
    QMessageBox::information(this, tr("Complete"), tr("Conversion complete"));
}

} // namespace checo::rimworld
