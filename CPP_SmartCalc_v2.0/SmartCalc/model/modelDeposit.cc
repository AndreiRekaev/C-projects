#include "modelDeposit.h"

void s21::DepositCalc::SetAmount(double a) noexcept { amount_ = a; }

void s21::DepositCalc::SetDuration(uint32_t d) noexcept { duration_ = d; }

void s21::DepositCalc::SetRate(double r) noexcept { rate_ = r; }

void s21::DepositCalc::SetTaxRate(double t) noexcept { taxRate_ = t; }

void s21::DepositCalc::SetReplanishment(uint32_t r) noexcept {
  replanishment_ = r;
}

void s21::DepositCalc::SetReplanishmentAmount(double r) noexcept {
  replanishmentAmount_ = r;
}

void s21::DepositCalc::SetWithdrawal(uint32_t w) noexcept { withdrawal_ = w; }

void s21::DepositCalc::SetWithdrawalAmount(double w) noexcept {
  withdrawalAmount_ = w;
}

void s21::DepositCalc::SetCapitalization(bool c) noexcept {
  capitalization_ = c;
}

void s21::DepositCalc::SetPaymentPeriod(uint32_t p) noexcept {
  paymentPeriod_ = p;
}

void s21::DepositCalc::CountDeposit(double& interestCharges, double& taxAmount,
                                    double& depAmount) const noexcept {
  double interestSum = 0;
  interestCharges = 0;
  depAmount = amount_;

  for (uint32_t i = 0; i < duration_; ++i) {
    if (replanishment_ != 0 && ((i + 1) % replanishment_ == 0)) {
      depAmount += replanishmentAmount_;
    }
    if (withdrawal_ != 0 && ((i + 1) % withdrawal_ == 0) &&
        depAmount > withdrawalAmount_) {
      depAmount -= withdrawalAmount_;
    }
    interestSum += depAmount * rate_ / 1200.;
    if ((paymentPeriod_ != 0 && ((i + 1) % paymentPeriod_ == 0)) ||
        i == duration_ - 1) {
      interestCharges += interestSum;
      taxAmount += interestSum * taxRate_ / 100;
      if (capitalization_) {
        depAmount += interestSum;
      }
      interestSum = 0;
    }
  }
}
