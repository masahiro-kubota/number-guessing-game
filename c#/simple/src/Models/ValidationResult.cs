namespace NumberGuessingGame.Models {
    public class ValidationResult<T> {
        public bool IsValid { get; init; }
        public T? Value {get; init; }
        public string? ErrorMessage {get; init; }

        public static ValidationResult<T> Success(T value)
            => new ValidationResult<T> {IsValid = true, Value = value, ErrorMessage = null};

        public static ValidationResult<T> Failure(string errorMessage)
            => new ValidationResult<T> {IsValid = false, Value = default, ErrorMessage = errorMessage};
    }
}

